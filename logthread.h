#ifndef LOGTHREAD_H
#define LOGTHREAD_H

#include <QThread>
#include <MultiWidgets/Widget.hpp>
#include <MultiWidgets/GrabManager.hpp>
#include <QTextStream>
#include <QFile>

#include <Radiant/Mutex.hpp>

#include "yaml-cpp/yaml.h"


class LogThread : public QThread
{
public:
    typedef std::map<long, Nimble::Vector2> FingerData;
    LogThread(MultiWidgets::Widget *widget, MultiWidgets::GrabManager *grapManager, QFile * file);
    void run();
    int exit(int retcode = 0);

    void setFingerData( const FingerData & data);
private:
    MultiWidgets::Widget * canvas;
    MultiWidgets::GrabManager * gm;
    YAML::Emitter out;
    QFile * file;
    bool running;
    
    Radiant::Mutex mutex;
    FingerData fingerdata;
};

#endif // LOGTHREAD_H
