#include "ConfigReader.h"

#include <QFile>
#include <QList>

ConfigReader::ConfigReader() :
    QObject(),
    _dbHost     (""),
    _dbName     (""),
    _dbUser     (""),
    _dbPassword (""),
    _dbPort     (0)
{
    QFile file (configFileName);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        while (!file.atEnd()) {
            QByteArray line = file.readLine();
            processLine(line);
        }

        file.close();
    }
}

ConfigReader::~ConfigReader()
{

}

void ConfigReader::processLine(QByteArray line)
{
    if (line.at(0) == '#')
        return;

    QList<QByteArray> lineSplit = line.split(' ');

    if (lineSplit.isEmpty())
        return;

    QString code = lineSplit.at(0);
    QString value = lineSplit.at(1);

    if (code == "DB_HOST")
        _dbHost = value;
    else if(code == "DB_PORT")
        _dbPort = value.toInt();
    else if(code == "DB_USER")
        _dbUser = value;
    else if(code == "DB_PASSWORD")
        _dbPassword = value;
    else if(code == "DB_NAME")
        _dbName = value;
}
