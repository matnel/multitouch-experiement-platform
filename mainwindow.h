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
};

#endif // MAINWINDOW_H
