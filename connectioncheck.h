#ifndef CONNECTIONCHECK_H
#define CONNECTIONCHECK_H

#include <QThread>
#include <MultiWidgets/Widget.hpp>
#include <MultiWidgets/GrabManager.hpp>

#include <QFile>

class ConnectionCheck : public QThread
{
public:
    ConnectionCheck(MultiWidgets::Widget *widget, QFile * logfile);
    void run();
    int exit(int retcode = 0);
    ~ConnectionCheck();
private:
    MultiWidgets::Widget * canvas;
    int maxFingers;
    QFile * log;
    bool runs;
};

#endif // LOGTHREAD_H
