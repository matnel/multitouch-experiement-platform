#include "experimenttrial.h"

#include "locationawarewidget.h"

#include "MultiWidgets/ImageWidget.hpp"
#include "MultiWidgets/StayInsideParentOperator.hpp"

#include <QtCore/qmath.h>
#include <QDebug>
#include <QDateTime>

#include <Resonant/DSPNetwork.hpp>
#include <Resonant/ModuleSamplePlayer.hpp>

#include "logthread.h"

#include "roundwidget.h"

#include "settings.h"
#include <sstream>

ExperimentTrial::ExperimentTrial(int id, RotationDirection direction, int distance, int size, int angle, int x1, int y1)
{
    this->id = id;
    this->direction = direction;

    this->distance = distance;
    this->size = size;
    this->angle = angle / 180.0 * M_PI;

    this->x1 = x1;
    this->y1 = y1;

    this->createUI();

    this->setFixed(true);
    this->setAllowRotation(false);

    this->setInputTransparent(true);
    this->setColor(0, 0, 0, 1);

    this->setSize(1920, 1080);

    // rotation direction
    MultiWidgets::ImageWidget * rotation = new MultiWidgets::ImageWidget();
    rotation->setFixed(true);
    rotation->setSize(100, 100);

    rotation->setColor(1,1,1,1);

    if( this->direction == ExperimentTrial::Clockwise ) {
        rotation->load("clockwise.png");
    } else {
        rotation->load("counterclockwise.png");
    }

    int max = distance > 200 ? distance : 200;

    rotation->setLocation( x1 - max, y1 - max);
    this->addChild( rotation );
}

void ExperimentTrial::input(MultiWidgets::GrabManager & gm, float dt) {
  MultiWidgets::Widget::input(gm, dt);


  std::stringstream ss;
  ss << "- time: ";
  ss << QTime().currentTime().toString("hh:mm:ss:zzz").toStdString() + "\n";

  ss << "  fingers:\n";

  int count = 0;
  for(ChildIterator it=childBegin(), end = childEnd(); it != end; ++it) {
    MultiWidgets::Widget::FingerIds::iterator start = it->grabFingerBegin();
    MultiWidgets::Widget::FingerIds::iterator last = it->grabFingerEnd();

    for( MultiWidgets::Widget::FingerIds::iterator finger = start; finger != last; finger++ ) {
      MultiTouch::Finger f = gm.findFinger(*finger);
      if(f.isNull())
        continue;

      ss << "    - id: " << f.id() << "\n";
      ss << "      position: " << f.tipLocation() << "\n";
      ++count;
    }
  }
  if(count == 0)
    return;

  ss << "  circles:\n";
  ss << "    - " << this->first->location() << "\n";
  ss << "    - " << this->second->location() << "\n";

  this->log->append(ss.str());
}

void ExperimentTrial::createUI()
{

    int x2 = qCos( this->angle ) * this->distance + x1;
    int y2 = qSin( this->angle ) * this->distance + y1;

    this->first = createMovable( x1 , y1);
    this->second = createMovable( x2, y2 );

    this->first->setTarget(x2, y2);
    this->second->setTarget(x1,y1);

}

LocationAwareWidget * ExperimentTrial::createMovable(int x, int y)
{
    LocationAwareWidget * a = new LocationAwareWidget();

    a->addOperator(new MultiWidgets::StayInsideParentOperator);
    a->setWidth(this->size);
    a->setHeight(this->size);

    if( DEBUG ) {
        a->setColor(1,0,0,50);
    } else {
        a->setColor(0,0,0,0);
    }
    a->setVelocity(0,0);

    a->setInputFlags(MultiWidgets::Widget::INPUT_MOTION_XY);

    a->setCenterLocation( Nimble::Vector2(x, y) );

    a->eventAddListener("target_reached", "check_targets", this);

    this->addChild(a);

    MultiWidgets::Widget * as = new RoundWidget();
    as->setWidth(this->size-10);
    as->setHeight(this->size-10);
    as->setColor(0.5, 0.5, 0, 1);

    as->setCenterLocation( Nimble::Vector2(x, y) );

    as->setAllowRotation(false);
    as->setFixed(true);

    this->addChild(as);

    return a;
}

void ExperimentTrial::processMessage(const char *id, Radiant::BinaryData &data)
{
    if( strcmp( id , "check_targets") == 0 ) {
        if( this->first->isTargetReached() && this->second->isTargetReached() ) {
            this->log->append("Targets reached\n");
            // close logs
            this->firstCheck->exit();
            this->secondCheck->exit();
            this->log->exit();

            this->hide();

            Resonant::ModuleSamplePlayer * player = Resonant::DSPNetwork::instance()->samplePlayer();
            player->playSample("task_done.wav",
                               1.0f,
                               1.0f,
                               0,
                               0,
                               false);
            eventSend("next_trial");
        }
    }
}

void ExperimentTrial::setApplication(MultiWidgets::GrabManager *application)
{
    this->application = application;

    // start logging
    QString path = "./logs/log-" + QDateTime::currentDateTime().toString("yyyyMMddhhmm") + "-" + QString::fromStdString(filename) + "-" + QString::number( this->id ) + "-";

    // start checking if connection is lost
    QFile * file1 = new QFile( path + "connection" );
    this->firstCheck= new ConnectionCheck(this->first, file1);
    this->firstCheck->start();
    this->secondCheck = new ConnectionCheck( this->second, file1);
    this->secondCheck->start();

    // start generic log
    QFile * file = new QFile( path + "log" );
    this->log = new LogThread(this, this->application, file );
    this->log->start();
}

ExperimentTrial::~ExperimentTrial()
{
    // remove threads
    delete this->firstCheck;
    delete this->secondCheck;
    delete this->log;

    // remove content
    this->deleteChildren();

    delete this;
}
