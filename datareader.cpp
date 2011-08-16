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

            if( reader->name() == "trial" ) {
                QXmlStreamAttributes attributes = reader->attributes();

                int id = attributes.value("id").toString().toInt();
                int angle = attributes.value("angle").toString().toInt();
                int size = attributes.value("size").toString().toInt();
                int x = attributes.value("grid_x").toString().toInt();
                int y = attributes.value("grid_y").toString().toInt();

                ExperimentTrial::RotationDirection direction;
                if( attributes.value("direction").toString() == "clock" ) {
                    direction = ExperimentTrial::Clockwise;
                } else {
                    direction = ExperimentTrial::Counterclockwise;
                }

                ExperimentTrial * trial = new ExperimentTrial(id, direction, size, angle, QPoint(x, y) );
            }



            reader->readNext();
    }

}
