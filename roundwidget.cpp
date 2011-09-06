#include "roundwidget.h"

#include "Luminous/Utils.hpp"

RoundWidget::RoundWidget() : MultiWidgets::Widget()
{
}

void RoundWidget::renderContent(Luminous::RenderContext &render)
{
    Luminous::Utils::glUsualBlend();

    int r = this->width() / 2;

    // TODO: Should use the set colors!
    glColor4f( 0.2, 0.5, 0.1, 1 );

    Luminous::Utils::glFilledCirclef( this->location().x +  r, this->location().y + r, r, 1000000 );

}
