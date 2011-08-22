#include "datareader.h"

#include "experimenttrial.h"

#include <QDebug>
#include <QTreeWidgetItem>

#include <QFileInfo>

DataReader::DataReader(QFile * file)
{
    file->open(QFile::ReadOnly);
    this->reader = new QXmlStreamReader( file );
    this->parseData();
}

void DataReader::parseData()
{
    while( ! reader->atEnd() ) {

            if( reader->name() == "trial" & reader->isStartElement() ) {
                QXmlStreamAttributes attributes = reader->attributes();

                int id = attributes.value("id").toString().toInt();

                int angle = attributes.value("angle").toString().toInt();
                int size = attributes.value("size").toString().toInt();
                int distance = attributes.value("distance").toString().toInt();

                int x = attributes.value("x1").toString().toInt();
                int y = attributes.value("y1").toString().toInt();

                ExperimentTrial::RotationDirection direction;
                if( attributes.value("direction").toString() == "clock" ) {
                    direction = ExperimentTrial::Clockwise;
                } else {
                    direction = ExperimentTrial::Counterclockwise;
                }

                ExperimentTrial * trial = new ExperimentTrial(id, direction, distance, size, angle, x, y );
                this->m_trials.push_back(trial);
            }


            if( reader->error() ) {
                qWarning() << "Something wrong with the inpurt file line " + reader->lineNumber() + reader->errorString();
            }

            reader->readNext();
    }

}

std::vector<ExperimentTrial*> DataReader::trials()
{
    return this->m_trials;
}
