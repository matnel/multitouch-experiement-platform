#include "mainwindow.h"

#include <QDebug>
#include <QFile>
#include "datareader.h"

MainWindow::MainWindow()
{
    QFile * f = new QFile("example.xml");
    DataReader * data = new DataReader( f );

    this->trials = data->trials();

    this->setFixed(true);
    this->setAllowRotation(false);

    this->setInputTransparent(true);
    this->setColor(0, 0, 0, 0);

    this->status = new MultiWidgets::TextBox();
    this->status->setText("Hello World!");
    this->addChild( this->status );
    this->status->setLocation(800,0);

    // initial setup
    this->currentTrial = 0;
    ExperimentTrial * trial;
    trial = trials[ this->currentTrial ];
    this->addChild(trial);
    trial->eventAddListener("next_trial", "next_trial", this );


}

void MainWindow::nextTrial()
{
    ExperimentTrial * trial;
    qDebug() << this->currentTrial;
    trial = trials[ this->currentTrial ];
    // causes seg fault!
    // this->deleteChild(trial);
    this->currentTrial++;
    if( this->currentTrial >= this->trials.size() ) {
        MultiWidgets::TextBox * text = new MultiWidgets::TextBox();
        text->setText("Test is over, thank you!");
        this->addChild( text );
        return;
    }
    trial = trials[ this->currentTrial ];
    trial->show();
   trial->eventAddListener("next_trial", "next_trial", this );
    this->addChild(trial);
    qDebug() << "Done!";
}

void MainWindow::processMessage(const char *id, Radiant::BinaryData &data)
{
    if( strcmp( id , "next_trial") == 0 ) {
        qDebug() << "Next trial!!!";
        this->nextTrial();
    }
}

