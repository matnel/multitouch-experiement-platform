#ifndef DATAREADER_H
#define DATAREADER_H

#include <QXmlStreamReader>
#include <QFile>

class DataReader
{
public:
    DataReader(QFile * file);
private:
    QXmlStreamReader * reader;
    void parseData();
};

#endif // DATAREADER_H
