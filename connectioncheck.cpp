#include "connectioncheck.h"

#include <QDebug>
#include <QTime>
#include <MultiWidgets/Widget.hpp>

ConnectionCheck::ConnectionCheck(MultiWidgets::Widget * widget)
{
    this->canvas = widget;
    this->maxFingers = 0;
}

void ConnectionCheck::run() {
    while( this->isRunning() ) {
        // qDebug() << QTime().currentTime().toString("hh:mm:ss:zzz");
        MultiWidgets::Widget * w = canvas;
        int fingers = w->grabFingerCount();
        if( fingers > this->maxFingers ) {
            this->maxFingers = fingers;
        }
        if( fingers < this->maxFingers ) {
            qDebug() << "Connection lost!";
            this->maxFingers = fingers;
        }
        this->msleep(2);
    }
}
