#ifndef LOCATIONAWAREWIDGET_H
#define LOCATIONAWAREWIDGET_H

#include <MultiWidgets/Widget.hpp>

class LocationAwareWidget : public MultiWidgets::Widget
{
public:
    LocationAwareWidget();
    virtual void interactionEnd (MultiWidgets::GrabManager &input);
};

#endif // LOCATIONAWAREWIDGET_H
