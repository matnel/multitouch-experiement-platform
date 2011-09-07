#include "logthread.h"

#include <QDebug>
#include <QTime>
#include <MultiWidgets/Widget.hpp>
#include <QFile>

#include "yaml-cpp/yaml.h"

LogThread::LogThread(MultiWidgets::Widget * widget, MultiWidgets::GrabManager * grapManager, QFile * file)
{
    this->canvas = widget;
    this->gm = grapManager;
    this->file = file;
}

void LogThread::run() {

    file->open( QIODevice::WriteOnly );

    QTextStream outF( this->file );

    outF << "";

    while( ! this->running ) {

        out << YAML::BeginSeq;

        out << YAML::BeginMap;
        out << YAML::Key << "time";
        out << YAML::Value << QTime().currentTime().toString("hh:mm:ss:zzz").toStdString();

        out << YAML::Key << "fingers";
        out << YAML::Value << YAML::BeginSeq;

        for ( MultiWidgets::Widget::ChildIterator child = canvas->childBegin(); child != canvas->childEnd(); ++child) {

           MultiWidgets::Widget::FingerIds::iterator start = child->grabFingerBegin();
           MultiWidgets::Widget::FingerIds::iterator last = child->grabFingerEnd();

           for( MultiWidgets::Widget::FingerIds::iterator finger = start; finger != last; finger++ ) {
                    out << YAML::BeginMap;

                    out << YAML::Key << "id";
                    qDebug() << "id" << *finger;
                    out << YAML::Key << *finger;
                    out << YAML::Key << "x";
                    out << YAML::Value << this->gm->latestFingerTipLocation( *finger ).x;
                    out << YAML::Key << "y";
                    out << YAML::Value << this->gm->latestFingerTipLocation( *finger ).y;

                    qDebug() << this->gm->latestFingerTipLocation( *finger ).y;

                    out << YAML::EndMap;
            }
         }
        out << YAML::EndSeq;

        out << YAML::EndMap;
        out << YAML::EndSeq;

        outF << out.c_str();
        outF.flush();

        this->msleep(2);
    }

    qDebug() << "Thread closed!";
    this->file->close();
}

int LogThread::exit(int retcode)
{
    this->running = false;
    return retcode;
}
