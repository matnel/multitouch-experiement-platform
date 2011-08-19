#include "experimenttrial.h"

#include <QtCore/qmath.h>

ExperimentTrial::ExperimentTrial(int id, RotationDirection direction, int distance, int size, int angle, QPoint gridPosition)
{
    this->id = id;
    this->direction = direction;

    this->distance = distance;
    this->size = size;
    this->angle = angle;

    this->gridPosition = gridPosition;

    this->createUI();

    this->setFixed(true);
    this->setAllowRotation(false);
}

void ExperimentTrial::createUI()
{
    int x = 500;
    int y = 500;

    MultiWidgets::Widget * a = new MultiWidgets::Widget();
    a->setWidth(this->size);
    a->setHeight(this->size);
    a->setColor(100,0,0,50);

    a->setCenterLocation( Nimble::Vector2(x, y) );

    this->addChild(a);

    MultiWidgets::Widget * b = new MultiWidgets::Widget();
    b->setWidth(this->size);
    b->setHeight(this->size);
    b->setColor(0,0,100,50);

    b->setCenterLocation( Nimble::Vector2( qCos( this->angle ) * this->distance + x , qSin( this->angle ) * this->distance + y) );

    this->addChild(b);
}
