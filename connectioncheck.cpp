#include "connectioncheck.h"

#include <QDebug>
#include <QTime>
#include <MultiWidgets/Widget.hpp>

#include <QTextStream>

ConnectionCheck::ConnectionCheck(MultiWidgets::Widget * widget, QFile * logfile)
{
    this->canvas = widget;
    this->maxFingers = 0;
    this->log = logfile;
}

void ConnectionCheck::run() {

    this->runs = true;

    if( ! this->log->isOpen() ) {
        this->log->open( QIODevice::WriteOnly );
    }

    QTextStream out( this->log );

    while( this->runs ) {
        // qDebug() << QTime().currentTime().toString("hh:mm:ss:zzz");
        MultiWidgets::Widget * w = canvas;
        int fingers = w->grabFingerCount();
        if( fingers > this->maxFingers ) {
            this->maxFingers = fingers;
        }
        if( fingers < this->maxFingers ) {
            out << QTime().currentTime().toString("hh:mm:ss:zzz");
            out << " connection lost!\n";
            out.flush();
            this->maxFingers = fingers;
        }
        this->msleep(2);
    }

    this->log->close();
}

int ConnectionCheck::exit(int retcode)
{
    this->runs = false;
    return retcode;
}

ConnectionCheck::~ConnectionCheck()
{
    // close thread
    this->runs = false;

    // make sure log is close
    log->close();
    delete log;
}
