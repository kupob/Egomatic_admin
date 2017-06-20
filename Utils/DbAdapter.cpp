#include "DbAdapter.h"

#include <QtSql/QSqlQuery>
#include <QVariant>
#include <QDebug>
#include <QSqlError>
#include <QSqlDriver>
#include <QSqlRecord>

DbAdapter* DbAdapter::_pinstance = 0;

DbAdapter::DbAdapter()
    : QObject()
{
    _db = QSqlDatabase::addDatabase("QPSQL", "egomatic");
}

DbAdapter *DbAdapter::instance()
{
    if(_pinstance == 0)
       _pinstance = new DbAdapter;
    return _pinstance;
}

bool DbAdapter::createConnection(QString hostName, QString dataBaseName, QString login, QString password, int port)
{
    _db.setHostName(hostName);
    _db.setDatabaseName(dataBaseName);
    _db.setUserName(login);
    _db.setPassword(password);
    if (port != 0)
        _db.setPort(port);

    bool result =_db.open();
    if (!result)
        qDebug() << _db.lastError().text();

    return result;
}

QString DbAdapter::getUuid()
{
    QList< QList<QVariant> > data;
    QSqlQuery query(_db);

    query.prepare("SELECT uuid_generate_v1mc();");

    getResult(query, data);
    QString result;

    if (!data.isEmpty() && !data.value(0).isEmpty())
        result = data.value(0).value(0).toString();

    return result;
}

QSqlQuery DbAdapter::getQuery()
{
    QSqlQuery result(_db);
    return result;
}

bool DbAdapter::getResult(QString query, QList< QList<QVariant> >& data)
{
    if (!_db.isOpen())
        return false;
    if (!data.isEmpty())
        data.clear();

    QSqlQuery sqlQuery(query);
    return getResult(sqlQuery, data);
}

bool DbAdapter::getResult(QSqlQuery query, bool execBatch)
{
    QList<QList<QVariant> > data;

    return getResult(query, data, execBatch);
}

bool DbAdapter::getResult(QSqlQuery query, QList<QList<QVariant> > &data, bool execBatch)
{
    if (!_db.isOpen())
        return false;
    if (!data.isEmpty())
        data.clear();

    bool ok;
    if (execBatch)
        ok = query.execBatch();
    else
        ok = query.exec();

    if (!ok)
    {
        QSqlError error = query.lastError();
        qDebug() << error.databaseText();
        qDebug() << error.driverText();
        qDebug() << error.text();
    }

    while (query.next())
    {
       int i = 0;
       QList<QVariant> singleResult;
       while (i < query.record().count())
       {
           singleResult.append(query.value(i));
           i++;
       }
       if (!singleResult.isEmpty())
           data.append(singleResult);
    }

    return ok;
}

bool DbAdapter::getResult(QSqlQuery query, QStringList &data, bool execBatch)
{
    QList<QList<QVariant> > rawData;

    bool ok = getResult(query, rawData, execBatch);

    foreach (auto subData, rawData)
        foreach (QVariant singleData, subData)
            data.append(singleData.toString());

    return ok;
}

bool DbAdapter::tryLogin(const QString &login, const QString &password, bool &isAdmin)
{
    QList< QList<QVariant> > data;
    QSqlQuery query(_db);

    query.prepare("SELECT isadmin FROM sys_user "
                  "WHERE login = :login "
                  "AND password = :password;");

    query.bindValue(":login", login);
    query.bindValue(":password", password);

    bool queryResult = getResult(query, data);
    if (!data.isEmpty())
        isAdmin = data.first().first().toBool();

    return queryResult && !data.isEmpty();
}
