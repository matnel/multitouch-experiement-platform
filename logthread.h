#ifndef LOGTHREAD_H
#define LOGTHREAD_H

#include <QThread>
#include <MultiWidgets/Widget.hpp>
#include <MultiWidgets/GrabManager.hpp>
#include <QTextStream>
#include <QFile>

#include "yaml-cpp/yaml.h"

class LogThread : public QThread
{
public:
    LogThread(MultiWidgets::Widget *widget, MultiWidgets::GrabManager *grapManager, QFile * file);
    void run();
    int exit(int retcode = 0);
private:
    MultiWidgets::Widget * canvas;
    MultiWidgets::GrabManager * gm;
    YAML::Emitter out;
    QFile * file;
    bool running;

};

#endif // LOGTHREAD_H
