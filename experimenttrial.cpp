#include "experimenttrial.h"

ExperimentTrial::ExperimentTrial(int id, RotationDirection direction, int distance, int size, int angle, QPoint gridPosition)
{
    this->id = id;
    this->direction = direction;

    this->distance = distance;
    this->size = size;
    this->angle = angle;

    this->gridPosition = gridPosition;
}
