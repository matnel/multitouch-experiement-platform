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

void LocationAwareWidget::input(MultiWidgets::GrabManager &gm, float dt)
{
    MultiWidgets::Widget::input(gm, dt);

    int ERROR_MARGIN = 50;

    if( qAbs( this->location().y - this->targetY ) <= ERROR_MARGIN && qAbs( this->location().x - this->targetX ) <= ERROR_MARGIN ) {
        this->setColor(0.5,0,1,1);
        this->targetReached = true;
    } else {
        this->setColor(1,0,0,1);
    }
}

void LocationAwareWidget::setTarget(int x, int y)
{
    this->targetX = x;
    this->targetY = y;
}

bool LocationAwareWidget::isTargetReached()
{
    return this->isTargetReached();
}
