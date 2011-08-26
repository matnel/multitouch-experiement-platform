#ifndef CONNECTIONCHECK_H
#define CONNECTIONCHECK_H

#include <QThread>
#include <MultiWidgets/Widget.hpp>
#include <MultiWidgets/GrabManager.hpp>

class ConnectionCheck : public QThread
{
public:
    ConnectionCheck(MultiWidgets::Widget *widget);
    void run();
private:
    MultiWidgets::Widget * canvas;
    int maxFingers;
};

#endif // LOGTHREAD_H
