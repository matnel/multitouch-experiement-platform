#include <MultiWidgets/SimpleSDLApplication.hpp>

#include <QDebug>

#include "logthread.h"
#include "datareader.h"
#include "experimenttrial.h"
#include "mainwindow.h"

int main(int argc, char ** argv)
{
  SDL_Init(SDL_INIT_VIDEO);

  MultiWidgets::SimpleSDLApplication app;

  if(!app.simpleInit(argc, argv))
    return 1;

  QFile * f = new QFile("example.xml");
  DataReader * data = new DataReader( f );

  // ExperimentTrial * trial = new ExperimentTrial(10, ExperimentTrial::Clockwise, 10, 100, 0, QPoint(0, 0) );

  MainWindow * main = new MainWindow( app.grabManager() );

  app.root()->addChild( main );

  return app.run();
}
