#include "locationawarewidget.h"

#include <QDebug>

LocationAwareWidget::LocationAwareWidget()
{
    this->targetReached = false;
}

void LocationAwareWidget::interactionEnd(MultiWidgets::GrabManager &input)
{
    MultiWidgets::Widget::interactionEnd(input);
    this->setRotation(0);
    this->setVelocity(0,0);
}

void LocationAwareWidget::grabFinger(long fingerId, MultiWidgets::GrabManager &gm)
{
    MultiWidgets::Widget::grabFinger(fingerId, gm);

}

void LocationAwareWidget::grabHand(long handId, MultiWidgets::GrabManager &gm)
{
    // DO NOT GRAP HAND
}

void LocationAwareWidget::input(MultiWidgets::GrabManager &gm, float dt)
{
    MultiWidgets::Widget::input(gm, dt);

    // set color based on number of fingers
    int fingers = this->grabFingerCount();

    if( fingers == 0 ) {
        this->setColor(1,0,0,0.95);
    }
    if( fingers == 1 ) {
        this->setColor(0,1,0,0.95);
    }
    if( fingers == 2 ) {
        this->setColor(0,0,1,0.95);
    }

    int ERROR_MARGIN = 50;

    if( qAbs( this->location().y - this->targetY ) <= ERROR_MARGIN && qAbs( this->location().x - this->targetX ) <= ERROR_MARGIN ) {
        this->setColor(0.5,0,1,1);
        // purukumia! ## todo fix
        if( !this->targetReached ) {
            this->targetReached = true;
            eventSend("target_reached");
        }
    } else {
        this->targetReached = false;
        // this->setColor(1,0,0,1);
    }
}

void LocationAwareWidget::setTarget(int x, int y)
{
    this->targetX = x;
    this->targetY = y;
}

bool LocationAwareWidget::isTargetReached()
{
    return this->targetReached;

}
