#include <MultiWidgets/SimpleSDLApplication.hpp>

#include <QDebug>

#include "logthread.h"
#include "datareader.h"
#include "experimenttrial.h"

int main(int argc, char ** argv)
{
  SDL_Init(SDL_INIT_VIDEO);

  MultiWidgets::SimpleSDLApplication app;

  if(!app.simpleInit(argc, argv))
    return 1;

//  LogThread * log = new LogThread( app.root(), app.grabManager() );
//  log->start();

  QFile * f = new QFile("example.xml");
  DataReader * data = new DataReader( f );

  ExperimentTrial * trial = new ExperimentTrial(10, ExperimentTrial::Clockwise, 10, 100, 0, QPoint(0, 0) );

  app.root()->addChild( trial );

  return app.run();
}
