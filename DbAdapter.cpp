#include "DbAdapter.h"

#include <QtSql/QSqlQuery>
#include <QVariant>
#include <QDebug>
#include <QSqlError>

DbAdapter* DbAdapter::_pinstance = 0;

DbAdapter::DbAdapter()
    : QObject()
{
    _db = QSqlDatabase::addDatabase("QPSQL", "em_db");
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

bool DbAdapter::getResult(QString selectionQuery, QList< QList<QVariant> >& data)
{
    if (!_db.isOpen())
        return false;
    if (!data.isEmpty())
        data.clear();

    QSqlQuery query(selectionQuery, _db);
    query.exec();

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
