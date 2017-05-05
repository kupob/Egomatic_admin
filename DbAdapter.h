#ifndef DBADAPTER_H
#define DBADAPTER_H

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QString>

class DbAdapter : public QObject
{
    Q_OBJECT
public:
    DbAdapter();
    static DbAdapter* instance();

    bool createConnection(QString hostName,
                          QString dataBaseName,
                          QString login,
                          QString password,
                          int port= 0);

    bool getResult(QString selectionQuery, QList< QList<QVariant> >& data);

private:
    static DbAdapter* _pinstance;

    QSqlDatabase _db;
};

#endif // DBADAPTER_H
