#include "logthread.h"

#include <QDebug>
#include <QTime>
#include <MultiWidgets/Widget.hpp>

LogThread::LogThread(MultiWidgets::Widget * widget, MultiWidgets::GrabManager * grapManager)
{
    this->canvas = widget;
    this->gm = grapManager;
}

void LogThread::run() {
    while( this->isRunning() ) {
        MultiWidgets::Widget * w = this->canvas->child(0);
        if( w->grabFingerCount() > 0 ) {
            qDebug() << QTime().currentTime().toString("hh:mm:ss:zzz");
            MultiWidgets::Widget::FingerIds::iterator start = w->grabFingerBegin();
            MultiWidgets::Widget::FingerIds::iterator last = w->grabFingerEnd();
            for( MultiWidgets::Widget::FingerIds::iterator finger = start; finger != last; finger++ ) {
                qDebug() << *finger;
                MultiTouch::Finger f = this->gm->getFinger( *finger );
                qDebug() << f.isNull();
            }
        }
        this->msleep(3);
    }
}
