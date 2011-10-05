#include "mainwindow.h"

#include <QDebug>
#include "datareader.h"

#include "delaydaddthread.h"

MainWindow::MainWindow(MultiWidgets::GrabManager * application, const std::string & fileName, int initial)
{
    QFile f(fileName.c_str());

    DataReader data( &f );

    this->trials = data.trials();

    this->setFixed(true);
    this->setAllowRotation(false);

    this->setInputTransparent(true);
    this->setColor(0, 0, 0, 0);

    this->status = new MultiWidgets::TextBox();
    this->status->setText("");
    this->status->setFixed(true);
    this->addChild( this->status );
    this->status->setLocation(800,0);

    this->application = application;
    this->filename = fileName;

    // initial setup
    this->currentTrial = initial;
    this->nextTrial();
}

ExperimentTrial * MainWindow::getCurrentTrial()
{
  return trials[ currentTrial ];
}

void MainWindow::update(float dt)
{
  MultiWidgets::Widget::update(dt);
  ExperimentTrial * trial = trials[this->currentTrial];
  for(ChildIterator it = childBegin(); it != childEnd(); ++it) {

    if(dynamic_cast<ExperimentTrial*>(*it) && *it != trial) {
      forgetChild(*it);
    }
  }

  if(nextTrialTime.sinceSecondsD() > 2.0f) {
    if(!trial->isFinished() && !hasChild(trial)) {
      addChild(trial);
    }
  }
}

void MainWindow::nextTrial()
{
    ExperimentTrial * trial;
    trial = trials[ this->currentTrial ];

    if(currentTrial > 0) {
      ExperimentTrial * current = trials[ currentTrial-1 ];
      current->finish();
    }
    this->currentTrial++;

    // when finished, show finished text
    if( this->currentTrial >= this->trials.size() ) {
        MultiWidgets::TextBox * text = new MultiWidgets::TextBox();
        text->setText("Test is over, thank you!");
        this->addChild( text );
        return;
    }

    trial = trials[ this->currentTrial ];
    trial->show();
    trial->setFilename(filename);
    trial->setApplication( this->application );

    trial->eventAddListener("next_trial", "next_trial", this );

    nextTrialTime = Radiant::TimeStamp::getTime();

    QString s = QString::number(this->currentTrial+1) + " of " + QString::number(this->trials.size());
    this->status->setText( s.toStdString() );

    static const float MARGIN = 30;
    trial->setSize( trial->width()-2*MARGIN, trial->height()-2*MARGIN );
    trial->setLocation(MARGIN, MARGIN);
    /*
    DelaydAddThread * thread = new DelaydAddThread(this, trial);
    thread->start();
    */
}

void MainWindow::processMessage(const char *id, Radiant::BinaryData &data)
{
    if( strcmp( id , "next_trial") == 0 ) {
        this->nextTrial();
    }
}

