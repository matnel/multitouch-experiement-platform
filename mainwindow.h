#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFile>
#include <MultiWidgets/Widget.hpp>
#include <MultiWidgets/GrabManager.hpp>
#include "experimenttrial.h"

class MainWindow : public MultiWidgets::Widget
{
public:
    MainWindow(MultiWidgets::GrabManager * application, QFile * file, int initial);
private:
    int currentTrial;
    void nextTrial();
    std::vector<ExperimentTrial *> trials;
    void processMessage(const char *id, Radiant::BinaryData &data);
    MultiWidgets::TextBox * status;
    MultiWidgets::GrabManager * application;
};

#endif // MAINWINDOW_H
