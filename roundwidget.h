#ifndef ROUNDWIDGET_H
#define ROUNDWIDGET_H

#include "MultiWidgets/Widget.hpp"

class RoundWidget : public MultiWidgets::Widget
{
public:
    RoundWidget();
    virtual void renderContent(Luminous::RenderContext & r);
    virtual void setColor(float r, float g, float b, float a);
private:
    float red;
    float blue;
    float green;
    float alpha;
};

#endif // ROUNDWIDGET_H
