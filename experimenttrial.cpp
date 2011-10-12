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
  : logger(0),
  first(0),
  second(0)
{  
    this->id = id;
    this->direction = direction;

    this->distance = distance;
    this->size = size;
    this->angle = angle / 180.0 * M_PI;

    this->target1 = Nimble::Vector2(x1,y1);
    this->target2 = this->target1 + Nimble::Vector2(distance, 0).rotate(angle);
    this->createUI();
this->setFixed(true);
    this->setAllowRotation(false);

    this->setInputTransparent(true);
    this->setColor(0, 0, 0, 1);

    this->setSize(1920, 1080);

// Deprecated, draw arrows from target circles instead
#if 0
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

    rotation->setLocation( target1.x - max, target1.y - max);
    this->addChild( rotation );
#endif

    // add logs

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

  ss << "  circles:\n";
  ss << "    - " << this->first->location() << "\n";
  ss << "    - " << this->second->location() << "\n";



  bool lost1 = first->isContactLost();
  bool lost2 = second->isContactLost();
  if(count == 0 && !lost1 && !lost2) {
    return;
  }
  if(lost1 || lost2) {
    ss << "  contact_lost:\n";
    ss << "    - circle1: " << lost1 << "\n";
    ss << "    - circle2: " << lost2 << "\n";
  }

  this->logger->append(ss.str());
}

void ExperimentTrial::createUI()
{
    bool flip = target1.y > target2.y;

    size_t targets[] = {0, 1};

    if(flip && direction == Clockwise) {targets[0]= 1; targets[1]= 0;}

    Nimble::Vector2 v = 0.5f*(target2-target1);
    Nimble::Vector2 off = (v + v.perpendicular());
    Nimble::Vector2 realTargets[] = { target1+off, target2-off };
    this->first = createMovable( target1, realTargets[0]);

    this->second = createMovable( target2, realTargets[1]);

    first->setTarget(realTargets[targets[0]]);
    second->setTarget(realTargets[targets[1]]);

    LocationAwareWidget * higher = first;
    LocationAwareWidget * lower = second;
    if(flip) {
      higher = second;
      lower = first;
    }
    
   higher->setDefaultColor(1,0,0);
    lower->setDefaultColor(0.3f, 0.3f, 1.0f);

    MultiWidgets::Widget * box = new RoundWidget();
    box->setColor(1,1,1,1);

    box->setSize(0.5f*(higher->size()));
    box->setFixed(true);
    box->setInputTransparent(true);
    box->setCenterLocation( 0.5f*higher->size() );
    higher->addChild(box);
}

LocationAwareWidget * ExperimentTrial::createMovable(Nimble::Vector2 pos, Nimble::Vector2 target)
{
    LocationAwareWidget * a = new LocationAwareWidget();

    a->setHeight( size );
    a->setWidth( size );

    a->addOperator(new MultiWidgets::StayInsideParentOperator);
    a->setCenterLocation( pos );

    if( DEBUG ) {
        a->setColor(1,0,0,50);
    } else {
        a->setColor(0,0,0,0);
    }
    a->setVelocity(0,0);

    a->setInputFlags(MultiWidgets::Widget::INPUT_MOTION_XY);

    a->eventAddListener("target_reached", "check_targets", this);

    this->addChild(a);

    MultiWidgets::Widget * as = new RoundWidget();
    as->setWidth(this->size-10);
    as->setHeight(this->size-10);
    as->setColor(0.5, 0.5, 0, 1);

    as->setCenterLocation( target );

    as->setAllowRotation(false);
    as->setFixed(true);

    this->addChild(as);

    return a;
}

bool ExperimentTrial::isFinished()
{
  return !(this->logger && this->logger->running);
}

void ExperimentTrial::finish()
{ 
  if(this->logger) {
    this->logger->exit();
    this->logger->wait(1000); // 1 sec
  }

  this->hide();
}

void ExperimentTrial::renderContent(Luminous::RenderContext & r)
{
    // draw arrows from target{1,2} to indicate direction to rotate
    Nimble::Vector2 v[] = { target1, target2 };

    Nimble::Vector2 center = 0.5f*(v[0]+v[1]);
    Radiant::Color c(1.0f, 0.5f, 0.3f, 0.9f);

    float sz = size * 1.5f;
    float w = 2.0f;

    for(size_t i=0; i < 2; ++i) {
     Nimble::Vector2 t = (v[i]-center).perpendicular().normalize(sz);
     if(direction == Counterclockwise || target1.y <= target2.y)
      t *= -1;

     Nimble::Vector2 p = (center-v[i]).normalize(sz/5);

     Nimble::Vector2 cps[] = {
      v[i],
      v[i]+0.5f*t - p,
      v[i]+t,
      v[i]+t+p
     };

     Nimble::Vector2 tangent = (cps[3] - cps[2]).normalize(sz/8);

     Nimble::Vector2 dir1 = tangent;
     dir1.rotate(Nimble::Math::PI * (4/5.0f));
     Nimble::Vector2 dir2 = tangent;
     dir2.rotate(Nimble::Math::PI * (-4/5.0f));

     r.drawCurve(cps, w, c.data());

     Nimble::Vector2 tip[] = {
      cps[3]+tangent,
      cps[3]+tangent+dir1,
      cps[3]+tangent+dir2,
      cps[3]+tangent
     };
     r.drawPolyLine(tip, 4, w, c.data());
    }

}

void ExperimentTrial::processMessage(const char *id, Radiant::BinaryData &data)
{
    if( strcmp( id , "check_targets") == 0 ) {
        if( this->first->isTargetReached() && this->second->isTargetReached() ) {
            this->logger->append("Targets reached\n");
            // close logs
            finish();

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
    //QFile * file1 = new QFile( path + "connection" );

    // start generic log
    QFile * file = new QFile( path + "log" );
    this->logger = new LogThread(this, this->application, file );
    this->logger->start();


    QString header( QString::number( this->id ) + " >> x " + QString::number( target1.x ) + " >> y " + QString::number( target1.y ) + " >> d " + QString::number( this->distance ) + " >> size " + QString::number( this->size ) + " >> angle " + QString::number( this->angle ) + "\n");
    this->logger->append( header.toStdString() );

}

ExperimentTrial::~ExperimentTrial()
{
    // remove threads
    delete this->logger;
}
