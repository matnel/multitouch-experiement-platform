#ifndef EXPERIMENTTRIAL_H
#define EXPERIMENTTRIAL_H

#include <QPoint>

class ExperimentTrial // : public ExperimentDataObject
{
    Q_ENUMS( RotationDirection );
public:
    enum RotationDirection {Clockwise, Counterclockwise};
    ExperimentTrial( int id, RotationDirection direction, int size, int angle, QPoint gridPosition );
private:
    int id;
    RotationDirection direction;
    int size;
    int angle;
    QPoint gridPosition;
};

#endif // EXPERIMENTTRIAL_H
