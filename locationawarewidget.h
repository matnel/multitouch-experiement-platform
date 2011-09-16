#ifndef LOCATIONAWAREWIDGET_H
#define LOCATIONAWAREWIDGET_H

#include <MultiWidgets/Widget.hpp>
#include <MultiWidgets/TextBox.hpp>
#include <MultiWidgets/GrabManager.hpp>

#include "roundwidget.h"

class LocationAwareWidget : public RoundWidget
{
public:
    LocationAwareWidget();
    virtual void interactionEnd (MultiWidgets::GrabManager &input);
    virtual void input(MultiWidgets::GrabManager &gm, float dt);
    virtual void grabFinger (long fingerId, MultiWidgets::GrabManager & gm);
    virtual void grabHand(long handId, MultiWidgets::GrabManager & gm);
    void setTarget(int x, int y);
    bool isTargetReached();
    bool isContactLost();

    void setDefaultColor(float r, float g, float b);

private:
    int targetX;
    int targetY;
    int initialX;
    int initialY;

    MultiWidgets::TextBox * text;

    bool targetReached;

    Nimble::Vector3 defColor;

    int maxFinger;
};

#endif // LOCATIONAWAREWIDGET_H
