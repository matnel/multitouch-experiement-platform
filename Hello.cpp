#include <MultiWidgets/SimpleSDLApplication.hpp>

#include <QDebug>

#include "logthread.h"

int main(int argc, char ** argv)
{
  SDL_Init(SDL_INIT_VIDEO);

  MultiWidgets::SimpleSDLApplication app;

  if(!app.simpleInit(argc, argv))
    return 1;

  for(int i = 0; i < 1; i++) {

    MultiWidgets::Widget * w = new MultiWidgets::Widget();

    w->setSize(Nimble::Vector2(100, 100));
    w->setLocation(Nimble::Vector2(i * 50, i * 50));
    w->setColor(Nimble::Vector4(1.0, 1.0f - i * 0.2, 0.3, 0.97));

    w->setRotation(45);

    app.root()->addChild(w);
   }

  LogThread * log = new LogThread( app.root(), app.grabManager() );
  log->start();

  return app.run();
}
