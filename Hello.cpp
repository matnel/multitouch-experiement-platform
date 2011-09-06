#include <MultiWidgets/SimpleSDLApplication.hpp>

#include <QDebug>
#include <QSound>

#include "logthread.h"
#include "datareader.h"
#include "experimenttrial.h"
#include "mainwindow.h"

#include <QDebug>

int main(int argc, char * argv[])
{
  SDL_Init(SDL_INIT_VIDEO);

  MultiWidgets::SimpleSDLApplication app;

  if( !app.simpleInit(argc, &argv[0] ) )
    return 1;

  // default file and default star location
  QFile * file = new QFile("example.xml");
  if( argc > 1 ) {
      file = new QFile( argv[1] );
  }

  int initial = -1;
  if( argc > 2 ) {
      initial = QString(argv[2]).toInt() - 1;
  }

  MainWindow * main = new MainWindow( app.grabManager(), file, initial );

  app.root()->addChild( main );

  return app.run();
}
