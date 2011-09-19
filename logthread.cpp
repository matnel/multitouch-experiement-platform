#include "logthread.h"
#include <QDebug>
#include <QTime>
#include <MultiWidgets/Widget.hpp>
#include <QFile>
#include <Radiant/Sleep.hpp>

LogThread::LogThread(MultiWidgets::Widget * widget, MultiWidgets::GrabManager * grapManager, QFile * file)
{
    this->canvas = widget;
    this->gm = grapManager;
    this->file = file;
}
    
void LogThread::setFingerData( const FingerData & data) {
  Radiant::Guard g(mutex);
  fingerdata = data;
}

void LogThread::append(const std::string & str) {
    Radiant::Guard g(mutex);
    toWrite.push(str);
}

void LogThread::run() {

    file->open( QIODevice::WriteOnly );

    QTextStream outF( this->file );

    //outF << "";

    while( ! this->running || !toWrite.empty()) {
        if(toWrite.empty()) {
            Radiant::Sleep::sleepMs(5);
            continue;
        }
        std::string write = toWrite.front();
        toWrite.pop();

        outF << write.c_str();
        outF.flush();
    }
#if 0
        this->msleep(7);

        mutex.lock();
        FingerData fd = fingerdata;
        mutex.unlock();

        if(fd.empty())
          continue;

        out << YAML::BeginSeq;

        out << YAML::BeginMap;
        out << YAML::Key << "time";
        out << YAML::Value << QTime().currentTime().toString("hh:mm:ss:zzz").toStdString();

        out << YAML::Key << "fingers";
        out << YAML::Value << YAML::BeginSeq;

        for(FingerData::iterator it = fd.begin(); it != fd.end(); ++it) {
		out << YAML::BeginMap;

		out << YAML::Key << "id";
		qDebug() << "id" << it->first;
		out << YAML::Value << it->first;
		out << YAML::Key << "x";
		out << YAML::Value << it->second.x;
		out << YAML::Key << "y";
		out << YAML::Value << it->second.y;

		qDebug() << it->second.y;

		out << YAML::EndMap;
        }
        
        out << YAML::EndSeq;

        out << YAML::EndMap;
        out << YAML::EndSeq;

        outF << out.c_str();
        outF.flush();

    }
#endif
    qDebug() << "Thread closed!";
    this->file->close();
}

int LogThread::exit(int retcode)
{
    this->running = false;
    return retcode;
}

LogThread::~LogThread()
{
    // close thread if not closed
    this->exit(-1);

    // close file and remove it
    this->file->close();
    delete file;
}
