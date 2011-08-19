#include "experimenttrial.h"

ExperimentTrial::ExperimentTrial(int id, RotationDirection direction, int distance, int size, int angle, QPoint gridPosition)
{
    this->id = id;
    this->direction = direction;

    this->distance = distance;
    this->size = size;
    this->angle = angle;

    this->gridPosition = gridPosition;

    this->createUI();
}

void ExperimentTrial::createUI()
{
    MultiWidgets::Widget * a = new MultiWidgets::Widget();
    a->setWidth(this->size);
    a->setHeight(this->size);
    a->setColor(100,0,0,50);

    this->addChild(a);
}
