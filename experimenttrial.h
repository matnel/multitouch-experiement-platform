#ifndef EXPERIMENTTRIAL_H
#define EXPERIMENTTRIAL_H

#include <MultiWidgets/Widget.hpp>
#include "locationawarewidget.h"

#include <QPoint>

class ExperimentTrial : public MultiWidgets::Widget
{
public:
    enum RotationDirection {Clockwise, Counterclockwise};
    ExperimentTrial( int id, RotationDirection direction, int distance, int size, int angle, QPoint gridPosition );
private:
    int id;
    RotationDirection direction;
    int size;
    double angle;
    int distance;
    QPoint gridPosition;
    void createUI();
    LocationAwareWidget * createMovable(int x, int y);
};

#endif // EXPERIMENTTRIAL_H
