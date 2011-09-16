#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFile>
#include <MultiWidgets/Widget.hpp>
#include <MultiWidgets/GrabManager.hpp>
#include "experimenttrial.h"

class MainWindow : public MultiWidgets::Widget
{
public:
    MainWindow(MultiWidgets::GrabManager * application, const std::string & fileName, int initial);

    ExperimentTrial * getCurrentTrial();
    virtual void update(float dt);
private:
    std::string filename;
    int currentTrial;
    void nextTrial();
    std::vector<ExperimentTrial *> trials;
    void processMessage(const char *id, Radiant::BinaryData &data);
    MultiWidgets::TextBox * status;
    MultiWidgets::GrabManager * application;
    Radiant::TimeStamp nextTrialTime;
};

#endif // MAINWINDOW_H
