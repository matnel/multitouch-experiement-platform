#ifndef LOCATIONAWAREWIDGET_H
#define LOCATIONAWAREWIDGET_H

#include <MultiWidgets/Widget.hpp>

class LocationAwareWidget : public MultiWidgets::Widget
{
public:
    LocationAwareWidget();
    virtual void interactionEnd (MultiWidgets::GrabManager &input);
    virtual void input(MultiWidgets::GrabManager &gm, float dt);
    void setTarget(int x, int y);
private:
    int targetX;
    int targetY;
};

#endif // LOCATIONAWAREWIDGET_H
