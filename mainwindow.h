#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <MultiWidgets/Widget.hpp>
#include "experimenttrial.h"

class MainWindow : public MultiWidgets::Widget
{
public:
    MainWindow();
private:
    int currentTrial;
    void nextTrial();
    std::vector<ExperimentTrial *> trials;
    void processMessage(const char *id, Radiant::BinaryData &data);
};

#endif // MAINWINDOW_H
