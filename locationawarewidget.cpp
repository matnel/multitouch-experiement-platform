#include "locationawarewidget.h"

LocationAwareWidget::LocationAwareWidget()
{
}

void LocationAwareWidget::interactionEnd(MultiWidgets::GrabManager &input)
{
    this->setRotation(0);
    this->setVelocity(0,0);
}
