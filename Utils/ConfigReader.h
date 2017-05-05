#ifndef CONFIGREADER_H
#define CONFIGREADER_H

#include <QObject>
#include <QString>

const QString configFileName = "./settings.conf";

class ConfigReader : public QObject
{
    Q_OBJECT
public:
    ConfigReader();
    ~ConfigReader();

    const QString dbHost     () const { return _dbHost     ; }
    const QString dbName     () const { return _dbName     ; }
    const QString dbUser     () const { return _dbUser     ; }
    const QString dbPassword () const { return _dbPassword ; }
    int     dbPort     () const { return _dbPort     ; }

private:
    void processLine(QByteArray line);

    QString _dbHost     ;
    QString _dbName     ;
    QString _dbUser     ;
    QString _dbPassword ;
    int     _dbPort     ;
};

#endif // CONFIGREADER_H
