#ifndef LOCATIONAWAREWIDGET_H
#define LOCATIONAWAREWIDGET_H

#include <MultiWidgets/Widget.hpp>
#include <MultiWidgets/TextBox.hpp>

class LocationAwareWidget : public MultiWidgets::Widget
{
public:
    LocationAwareWidget();
    virtual void interactionEnd (MultiWidgets::GrabManager &input);
    virtual void input(MultiWidgets::GrabManager &gm, float dt);
    void setTarget(int x, int y);
    bool isTargetReached();
private:
    int targetX;
    int targetY;
    MultiWidgets::TextBox * text;
    bool targetReached;
};

#endif // LOCATIONAWAREWIDGET_H
