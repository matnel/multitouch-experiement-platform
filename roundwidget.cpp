#include "roundwidget.h"

#include "Luminous/Utils.hpp"

RoundWidget::RoundWidget() : MultiWidgets::Widget()
{
    this->red = 0.5;
    this->green = 0.2;
    this->blue = 0;
    this->alpha = 1;
}

void RoundWidget::renderContent(Luminous::RenderContext &render)
{
    Luminous::Utils::glUsualBlend();

    int r = this->width() / 2;

    // TODO: Should use the set colors!
    glColor4f( red, green, blue, alpha );

    Luminous::Utils::glFilledCirclef( this->location().x +  r, this->location().y + r, r, 1000000 );

}

void RoundWidget::setColor(float r, float g, float b, float a)
{
    this->red = r;
    this->green = g;
    this->blue = b;
    this->alpha = a;
}
