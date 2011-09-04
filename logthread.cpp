#include "logthread.h"

#include <QDebug>
#include <QTime>
#include <MultiWidgets/Widget.hpp>

#include "yaml-cpp/yaml.h"

LogThread::LogThread(MultiWidgets::Widget * widget, MultiWidgets::GrabManager * grapManager)
{
    this->canvas = widget;
    this->gm = grapManager;
}

void LogThread::run() {
    while( this->isRunning() ) {

        out << YAML::BeginMap;
        out << YAML::Key << "time";
        out << YAML::Value << QTime().currentTime().toString("hh:mm:ss:zzz").toStdString();

        MultiWidgets::Widget * w = canvas->child(0);
        MultiWidgets::Widget::FingerIds::iterator start = w->grabFingerBegin();
        MultiWidgets::Widget::FingerIds::iterator last = w->grabFingerEnd();

        out << YAML::BeginSeq;

        for( MultiWidgets::Widget::FingerIds::iterator finger = start; finger != last; finger++ ) {
            MultiTouch::Finger f = this->gm->findFinger( *finger );

            out << YAML::BeginMap;

            out << YAML::Key << "id";
            out << YAML::Value << f.id();
            out << YAML::Key << "x";
            out << YAML::Value << f.tipLocation().x;
            out << YAML::Key << "y";
            out << YAML::Value << f.tipLocation().y;

            out << YAML::EndMap;
        }

        out << YAML::EndSeq;

        out << YAML::EndMap;
        qDebug() << out.c_str();
        this->msleep(2);
    }
}
