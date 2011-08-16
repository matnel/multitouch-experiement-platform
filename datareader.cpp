#include "datareader.h"

#include "experimenttrial.h"

DataReader::DataReader(QFile * file)
{
    this->reader = new QXmlStreamReader( file );
}

void DataReader::parseData()
{

    while( ! reader->atEnd() ) {
        if( reader->isStartElement() ) {
            if( reader->name() == "trial" ) {
                QXmlStreamAttributes attributes = reader->attributes();
                // fixme
                int id = attributes.value("id").toString().toInt();
                ExperimentTrial::RotationDirection direction;
                if( attributes.value("direction").toString() == "clock" ) {
                    direction = ExperimentTrial::Clockwise;
                } else {
                    direction = ExperimentTrial::Counterclockwise;
                }
                int angle = attributes.value("angle").toString().toInt();
                int size = attributes.value("size").toString().toInt();
                int x = attributes.value("grid_x").toString().toInt();
                int y = attributes.value("grid_y").toString().toInt();
                ExperimentTrial * trial = new ExperimentTrial(id, direction, size, angle, QPoint(x, y) );
            }
        }
    }

}
