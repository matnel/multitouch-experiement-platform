#ifndef DATAREADER_H
#define DATAREADER_H

#include <QXmlStreamReader>
#include <QFile>

#include "experimenttrial.h"

class DataReader
{
public:
    DataReader(QFile * file);
    std::vector<ExperimentTrial*> trials();
private:
    QFile * file;
    void parseData();
    std::vector<ExperimentTrial*> m_trials;
};

#endif // DATAREADER_H
