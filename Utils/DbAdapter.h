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

    QString getUuid();
    QSqlQuery getQuery();

    bool tryLogin(const QString& login, const QString& password);

    bool getResult(QString query, QList< QList<QVariant> >& data);
    bool getResult(QSqlQuery query, bool execBatch = false);
    bool getResult(QSqlQuery query, QList< QList<QVariant> >& data, bool execBatch = false);
    bool getResult(QSqlQuery query, QStringList& data, bool execBatch = false);

private:
    static DbAdapter* _pinstance;

    QSqlDatabase _db;
};

#endif // DBADAPTER_H
