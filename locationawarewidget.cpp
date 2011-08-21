#include "locationawarewidget.h"

#include <QDebug>

LocationAwareWidget::LocationAwareWidget()
{
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
    qDebug() << this->location().x;
}

void LocationAwareWidget::setTarget(int x, int y)
{
    this->targetX = x;
    this->targetY = y;
}
