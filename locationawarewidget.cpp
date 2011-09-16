#include "locationawarewidget.h"

#include <QDebug>

#include "settings.h"

LocationAwareWidget::LocationAwareWidget()
    : maxFinger(0)
{
    this->targetReached = false;

    this->defColor.x = 1.0;
    this->defColor.y = 0.0;
    this->defColor.z = 0.0;

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

    int fingers = this->grabFingerCount();

    if( DEBUG ) {

        // set color based on number of fingers

        if( fingers == 0 ) {
            this->setColor( this->defColor.x, this->defColor.y, this->defColor.z , 0.95);
        }
        if( fingers == 1 ) {
            this->setColor(0,1,0,0.95);
        }
        if( fingers == 2 ) {
            this->setColor(0,0,1,0.95);
        }

    }

    int middleX = initialX + ( targetX - initialX ) / 2;
    int middleY = initialY + ( targetY - initialY ) / 2;

    Nimble::Vector2 v1( initialX - middleX, initialY - middleY );
    Nimble::Vector2 v2( (this->location().x + this->width() / 2) - middleX, ( this->location().x + this->width() / 2) - middleY );

    // qDebug() << v1.x << " " << v1.y;
    // qDebug() << v2.x << " " << v2.y;

    float angle = acos( (v1.x * v2.x + v1.y * v2.y ) / ( v1.length() * v2.length() )  );

    // qDebug() << angle;

    if( fingers > this->maxFinger ) {
        this->maxFinger = fingers;
    }

    int ERROR_MARGIN = 20;

    if( qAbs( ( this->location().y + this->width() / 2)  - this->targetY ) <= ERROR_MARGIN && qAbs( ( this->location().x + this->width() / 2) - this->targetX ) <= ERROR_MARGIN ) {
        if( DEBUG ) {
            this->setColor(0.5,0,1,1);
        }
        // purukumia! ## todo fix
        if( !this->targetReached ) {
            this->targetReached = true;
            eventSend("target_reached");
        }
    } else {
        this->targetReached = false;
    }
}

bool LocationAwareWidget::isContactLost()
{
    if( this->grabFingerCount() < this->maxFinger ) {
        this->maxFinger = this->grabFingerCount();
        return true;
    }
    return false;
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

void LocationAwareWidget::setDefaultColor(float r, float g, float b)
{
  this->defColor.x = r;
  this->defColor.y = g;
  this->defColor.z = b;
}
