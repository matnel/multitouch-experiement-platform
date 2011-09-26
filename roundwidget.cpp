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

    float rgba[] = {red, green, blue, alpha };
    render.drawCircle(0.5f*this->size(), r, rgba);
}

void RoundWidget::setColor(float r, float g, float b, float a)
{
    this->red = r;
    this->green = g;
    this->blue = b;
    this->alpha = a;
}
