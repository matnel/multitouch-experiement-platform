#include <MultiWidgets/SimpleSDLApplication.hpp>

#include <QDebug>
#include <QSound>

#include "logthread.h"
#include "datareader.h"
#include "experimenttrial.h"
#include "mainwindow.h"

#include <QDebug>


class App : public MultiWidgets::SimpleSDLApplication
{
public:
  App() : mw(0) {}
  bool keyPressEvent(int ascii, int special, int modifiers)
  {
    LogThread * logger = 0;
    if(mw) {
      if(!mw->getCurrentTrial())
        return true;
      logger = mw->getCurrentTrial()->getLogger();
      if(!logger)
        return true;
    }
    if(ascii == 'h' && logger) {

      logger->append("Subjectively hard trial!\n");
      return true;
    } else if(ascii == 't' && logger) {
      logger->append("Tracking problem!\n");
      return true;
    } else if(ascii == 'n' && logger) {
      mw->nextTrial();
      logger->append("Skipping trial!\n");
      return true;
    } else {
      if(logger && ( (ascii >= '0' && ascii <= '9') || (ascii >= 'a' && ascii <= 'z') )) {
        std::string p("Key pressed: "); p += ascii; p += '\n';
        logger->append(p.c_str());
      }
      return MultiWidgets::SimpleSDLApplication::keyPressEvent(ascii, special, modifiers);
    }
  }
  void setMainWindow(MainWindow * win) { mw = win; }
private:
  MainWindow * mw;
};

int main(int argc, char * argv[])
{
  SDL_Init(SDL_INIT_VIDEO);

  App app;

  if( !app.simpleInit(argc, &argv[0] ) )
    return 1;

  // default file and default star location
  std::string file = "example.xml";

  if( argc > 1 ) {
      file = argv[1];
  }

  int initial = -1;
  if( argc > 2 ) {
      initial = QString(argv[2]).toInt() - 1;
  }

  MainWindow * main = new MainWindow( app.grabManager(), file, initial );

  app.setMainWindow(main);

  app.root()->addChild( main );

  return app.run();
}
