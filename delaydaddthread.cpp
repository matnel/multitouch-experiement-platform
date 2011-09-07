#include "delaydaddthread.h"


DelaydAddThread::DelaydAddThread(MultiWidgets::Widget *parent, MultiWidgets::Widget *child, long seconds)
{
    this->parent = parent;
    this->child = child;
    this->seconds = seconds;
}

void DelaydAddThread::run()
{
    this->sleep( this->seconds );
    this->parent->addChild( this->child );
}
