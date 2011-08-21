#include "experimenttrial.h"

#include "locationawarewidget.h"

#include <QtCore/qmath.h>

ExperimentTrial::ExperimentTrial(int id, RotationDirection direction, int distance, int size, int angle, QPoint gridPosition)
{
    this->id = id;
    this->direction = direction;

    this->distance = distance;
    this->size = size;
    this->angle = angle / 180.0 * M_PI;

    this->gridPosition = gridPosition;

    this->createUI();

    this->setFixed(true);
    this->setAllowRotation(false);

    this->setInputTransparent(true);
    this->setColor(0, 0, 0, 0);

    this->setSize(1000, 1000);
}

void ExperimentTrial::createUI()
{
    int x = 500;
    int y = 500;

    createMovable(x,y);

    x = qCos( this->angle ) * this->distance + x;
    y = qSin( this->angle ) * this->distance + y;

    createMovable( x, y);
}

void ExperimentTrial::createMovable(int x, int y)
{
    LocationAwareWidget * a = new LocationAwareWidget();
    a->setWidth(this->size);
    a->setHeight(this->size);
    a->setColor(100,0,0,50);
    a->setVelocity(0,0);

    a->setCenterLocation( Nimble::Vector2(x, y) );

    this->addChild(a);

    MultiWidgets::Widget * as = new MultiWidgets::Widget();
    as->setWidth(this->size-10);
    as->setHeight(this->size-10);
    as->setColor(100,50,0,50);

    as->setCenterLocation( Nimble::Vector2(x, y) );

    as->setAllowRotation(false);
    as->setFixed(true);

    this->addChild(as);
}
