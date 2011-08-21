#include "mainwindow.h"

#include <QFile>
#include "datareader.h"

MainWindow::MainWindow()
{
    this->currentTrial = 0;

    QFile * f = new QFile("example.xml");
    DataReader * data = new DataReader( f );

    this->trials = data->trials();

    this->setFixed(true);
    this->setAllowRotation(false);

    this->setInputTransparent(true);
    this->setColor(0, 0, 0, 0);

    // initial setup
    ExperimentTrial * trial;
    trial = trials[ 0 ];
    this->addChild(trial);

}

void MainWindow::nextTrial()
{
    ExperimentTrial * trial;
    trial = trials[ this->currentTrial ];
    trial->hide();
    this->currentTrial++;
    if( this->currentTrial > this->trials.size() ) {
        return;
    }
    trial = trials[ this->currentTrial ];
    trial->show();
    this->addChild(trial);
}
