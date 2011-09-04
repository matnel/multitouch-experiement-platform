#include "experimenttrial.h"

#include "locationawarewidget.h"

#include <QtCore/qmath.h>
#include <QDebug>
#include <QSound>

ExperimentTrial::ExperimentTrial(int id, RotationDirection direction, int distance, int size, int angle, int x1, int y1)
{

    qDebug() << size;

    this->id = id;
    this->direction = direction;

    this->distance = distance;
    this->size = size;
    this->angle = angle / 180.0 * M_PI;

    this->x1 = x1;
    this->y1 = y1;

    this->createUI();

    this->setFixed(true);
    this->setAllowRotation(false);

    this->setInputTransparent(true);
    this->setColor(0, 0, 0, 0);

    this->setSize(1000, 1000);
}

void ExperimentTrial::createUI()
{

    int x2 = qCos( this->angle ) * this->distance + x1;
    int y2 = qSin( this->angle ) * this->distance + y1;

    this->first = createMovable( x1 , y1);
    this->second = createMovable( x2, y2 );

    this->first->setTarget(x2, y2);
    this->second->setTarget(x1,y1);

    // start tchecking if connection is lost
    this->firstCheck= new ConnectionCheck(this->first);
    this->firstCheck->start();
    this->secondCheck = new ConnectionCheck( this->second );
    this->secondCheck->start();

}

LocationAwareWidget * ExperimentTrial::createMovable(int x, int y)
{
    LocationAwareWidget * a = new LocationAwareWidget();
    a->setWidth(this->size);
    a->setHeight(this->size);
    a->setColor(100,0,0,50);
    a->setVelocity(0,0);

    a->setInputFlags(MultiWidgets::Widget::INPUT_MOTION_XY);

    a->setCenterLocation( Nimble::Vector2(x, y) );

    a->eventAddListener("target_reached", "check_targets", this);

    this->addChild(a);

    MultiWidgets::Widget * as = new MultiWidgets::Widget();
    as->setWidth(this->size-10);
    as->setHeight(this->size-10);
    as->setColor(100,50,0,50);

    as->setCenterLocation( Nimble::Vector2(x, y) );

    as->setAllowRotation(false);
    as->setFixed(true);

    this->addChild(as);

    return a;
}

void ExperimentTrial::processMessage(const char *id, Radiant::BinaryData &data)
{
    if( strcmp( id , "check_targets") == 0 ) {
        if( this->first->isTargetReached() && this->second->isTargetReached() ) {
            this->firstCheck->quit();
            this->secondCheck->quit();
            this->hide();
            // QSound::play("task_done.wav");
            eventSend("next_trial");
        }
    }
}
