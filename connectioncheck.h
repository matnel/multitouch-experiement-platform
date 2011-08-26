#ifndef CONNECTIONCHECK_H
#define CONNECTIONCHECK_H

#include <QThread>
#include <MultiWidgets/Widget.hpp>
#include <MultiWidgets/GrabManager.hpp>

class ConnectionCheck : public QThread
{
public:
    ConnectionCheck(MultiWidgets::Widget *widget, MultiWidgets::GrabManager *grapManager);
    void run();
private:
    MultiWidgets::Widget * canvas;
    MultiWidgets::GrabManager * gm;
};

#endif // LOGTHREAD_H
