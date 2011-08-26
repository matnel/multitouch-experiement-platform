#include "connectioncheck.h"

#include <QDebug>
#include <QTime>
#include <MultiWidgets/Widget.hpp>

ConnectionCheck::ConnectionCheck(MultiWidgets::Widget * widget, MultiWidgets::GrabManager * grapManager)
{
    this->canvas = widget;
    this->gm = grapManager;
}

void ConnectionCheck::run() {
    while( this->isRunning() ) {
        qDebug() << QTime().currentTime().toString("hh:mm:ss:zzz");
        MultiWidgets::Widget * w = canvas->child(0);
        MultiWidgets::Widget::FingerIds::iterator start = w->grabFingerBegin();
        MultiWidgets::Widget::FingerIds::iterator last = w->grabFingerEnd();
        for( MultiWidgets::Widget::FingerIds::iterator finger = start; finger != last; finger++ ) {
            MultiTouch::Finger f = this->gm->findFinger( *finger );
            qDebug() << f.id();
            qDebug() << f.tipLocation().x;
            qDebug() << f.tipLocation().y;
        }
        this->msleep(2);
    }
}
