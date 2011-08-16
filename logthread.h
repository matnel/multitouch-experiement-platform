#ifndef LOGTHREAD_H
#define LOGTHREAD_H

#include <QThread>
#include <MultiWidgets/Widget.hpp>
#include <MultiWidgets/GrabManager.hpp>

class LogThread : public QThread
{
public:
    LogThread(MultiWidgets::Widget *widget, MultiWidgets::GrabManager *grapManager);
    void run();
private:
    MultiWidgets::Widget * canvas;
    MultiWidgets::GrabManager * gm;
};

#endif // LOGTHREAD_H
