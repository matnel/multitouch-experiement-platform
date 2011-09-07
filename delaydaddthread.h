#ifndef DELAYDADDTHREAD_H
#define DELAYDADDTHREAD_H

#include <QThread>
#include "MultiWidgets/Widget.hpp"

class DelaydAddThread : public QThread
{
    Q_OBJECT
public:
    DelaydAddThread(MultiWidgets::Widget * parent, MultiWidgets::Widget * child, long seconds = 1);
    virtual void run();
private:
    long seconds;
    MultiWidgets::Widget * parent;
    MultiWidgets::Widget * child;
};

#endif // DELAYDADDTHREAD_H
