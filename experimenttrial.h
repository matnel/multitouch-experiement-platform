#ifndef EXPERIMENTTRIAL_H
#define EXPERIMENTTRIAL_H

#include <MultiWidgets/Widget.hpp>

#include <QPoint>

class ExperimentTrial : MultiWidgets::Widget
{
public:
    enum RotationDirection {Clockwise, Counterclockwise};
    ExperimentTrial( int id, RotationDirection direction, int distance, int size, int angle, QPoint gridPosition );
private:
    int id;
    RotationDirection direction;
    int size;
    int angle;
    int distance;
    QPoint gridPosition;
};

#endif // EXPERIMENTTRIAL_H
