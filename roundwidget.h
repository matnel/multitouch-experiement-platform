#ifndef ROUNDWIDGET_H
#define ROUNDWIDGET_H

#include "MultiWidgets/Widget.hpp"

class RoundWidget : public MultiWidgets::Widget
{
public:
    RoundWidget();
    virtual void renderContent(Luminous::RenderContext & r);
};

#endif // ROUNDWIDGET_H
