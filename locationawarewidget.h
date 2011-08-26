#ifndef LOCATIONAWAREWIDGET_H
#define LOCATIONAWAREWIDGET_H

#include <MultiWidgets/Widget.hpp>
#include <MultiWidgets/TextBox.hpp>
#include <MultiWidgets/GrabManager.hpp>

class LocationAwareWidget : public MultiWidgets::Widget
{
public:
    LocationAwareWidget();
    virtual void interactionEnd (MultiWidgets::GrabManager &input);
    virtual void input(MultiWidgets::GrabManager &gm, float dt);
    virtual void grabFinger (long fingerId, MultiWidgets::GrabManager & gm);
    virtual void grabHand(long handId, MultiWidgets::GrabManager & gm);
    void magic(long handId, MultiWidgets::GrabManager & gm, bool inside);
    void setTarget(int x, int y);
    bool isTargetReached();
    void setSecondary(LocationAwareWidget * widget);
private:
    int targetX;
    int targetY;
    MultiWidgets::TextBox * text;
    bool targetReached;
    LocationAwareWidget * secondary;
};

#endif // LOCATIONAWAREWIDGET_H
