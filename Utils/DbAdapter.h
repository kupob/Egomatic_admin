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

    bool tryLogin(const QString& login, const QString& password);
    bool getDrinks(QList< QList<QVariant> >& data);

private:
    bool getResult(QString query, QList< QList<QVariant> >& data);
    bool getResult(QSqlQuery query, QList< QList<QVariant> >& data);

private:
    static DbAdapter* _pinstance;

    QSqlDatabase _db;
};

#endif // DBADAPTER_H
