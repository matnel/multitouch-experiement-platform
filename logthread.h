#ifndef LOGTHREAD_H
#define LOGTHREAD_H

#include <QThread>
#include <MultiWidgets/Widget.hpp>
#include <MultiWidgets/GrabManager.hpp>
#include <QTextStream>
#include <QFile>
#include <queue>
#include <Radiant/Mutex.hpp>

class LogThread : public QThread
{
public:
    typedef std::map<long, Nimble::Vector2> FingerData;

    LogThread(MultiWidgets::Widget *widget, MultiWidgets::GrabManager *grapManager, QFile * file);
    ~LogThread();

    void run();
    int exit(int retcode = 0);

    void append(const std::string & str);

    void setFingerData( const FingerData & data);
private:
    MultiWidgets::Widget * canvas;
    MultiWidgets::GrabManager * gm;
    QFile * file;
    bool running;

    std::queue<std::string> toWrite;
    
    Radiant::Mutex mutex;
    FingerData fingerdata;
};

#endif // LOGTHREAD_H
