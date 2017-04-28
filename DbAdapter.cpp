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
    qDebug() << _db.lastError().text();
}

bool DbAdapter::getResult(QString selectionQuery)
{
    if (!_db.isOpen())
        return false;

    QSqlQuery query(selectionQuery);
    query.exec();

    while (query.next())
    {
       int i = 0;
       while (query.value(i).isValid())
       {
           QString field = query.value(i).toString();
           i++;
       }
    }

    return true;
}
