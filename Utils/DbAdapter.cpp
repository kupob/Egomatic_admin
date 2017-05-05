#include "DbAdapter.h"

#include <QtSql/QSqlQuery>
#include <QVariant>
#include <QDebug>
#include <QSqlError>
#include <QSqlDriver>

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

bool DbAdapter::getResult(QString query, QList< QList<QVariant> >& data)
{
    if (!_db.isOpen())
        return false;
    if (!data.isEmpty())
        data.clear();

    QSqlQuery sqlQuery(query);
    return getResult(sqlQuery, data);
}

bool DbAdapter::getResult(QSqlQuery query, QList<QList<QVariant> > &data)
{
    if (!_db.isOpen())
        return false;
    if (!data.isEmpty())
        data.clear();

    if (!query.exec())
    {
        qDebug() << _db.lastError();
        qDebug() << query.lastError();
    }

    while (query.next())
    {
       int i = 0;
       QList<QVariant> singleResult;
       while (query.value(i).isValid())
       {
           singleResult.append(query.value(i));
           i++;
       }
       if (!singleResult.isEmpty())
           data.append(singleResult);
    }

    return !data.isEmpty();
}

bool DbAdapter::tryLogin(const QString &login, const QString &password)
{
    QList< QList<QVariant> > data;
    QSqlQuery query(_db);

    query.prepare("SELECT userid FROM sys_user "
                  "WHERE login = ? "
                  "AND password = ?;");

    query.addBindValue(login);
    query.addBindValue(password);

    bool queryResult = getResult(query, data);

    return queryResult && !data.isEmpty();
}

bool DbAdapter::getDrinks(QList<QList<QVariant> > &data)
{
    QSqlQuery query(_db);

    query.prepare("SELECT drinkid, name, cost, abv, ibu, description FROM public.em_drink WHERE isactive = true");

    bool queryResult = getResult(query, data);

    return queryResult && !data.isEmpty();
}
