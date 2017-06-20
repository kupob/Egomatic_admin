#include "UserGateway.h"
#include <QSqlQuery>
#include <QDebug>

UserGateway::UserGateway()
{
    _db = DbAdapter::instance();
}

bool UserGateway::getItems(QList<User> &data)
{
    QSqlQuery query = _db->getQuery();

    query.prepare("SELECT userid, login, password, name, isadmin, isactive FROM public.sys_user WHERE isactive = true");

    QList<QList<QVariant> > rawData;
    bool queryResult = _db->getResult(query, rawData);
    data = User::convertFromData(rawData);

    return queryResult && !data.isEmpty();
}

bool UserGateway::saveItems(QList<User> data)
{
    QSqlQuery selectQuery = _db->getQuery();
    QSqlQuery insertQuery = _db->getQuery();
    QSqlQuery updateQuery = _db->getQuery();

    QStringList existsIdList;
    selectQuery.prepare("SELECT DISTINCT userid FROM sys_user; ");
    _db->getResult(selectQuery, existsIdList);

    insertQuery.prepare(" INSERT INTO sys_user("
                  " userid, login, password, name, isadmin, isactive)"
                  " VALUES (:userid, :login, :password, :name, :isadmin, :isactive)"
                  " ON CONFLICT (userid) DO NOTHING ;");

    updateQuery.prepare(" UPDATE sys_user"
                        " SET login=:login, password=:password, name=:name, isadmin=:isadmin, isactive=:isactive "
                        " WHERE userid=:userid;");

    QVariantList insert_userId,
                 insert_login,
                 insert_password,
                 insert_name,
                 insert_isAdmin,
                 insert_isActive;

    QVariantList update_userId,
                 update_login,
                 update_password,
                 update_name,
                 update_isAdmin,
                 update_isActive;

    foreach (User user, data)
    {
        if (!existsIdList.contains(user.userId))
        {
            insert_userId   .append ( user.userId    );
            insert_login    .append ( user.login     );
            insert_password .append ( user.password  );
            insert_name     .append ( user.name      );
            insert_isAdmin  .append ( user.isAdmin   );
            insert_isActive .append ( user.isActive  );
        }
        else
        {
            update_userId   .append ( user.userId    );
            update_login    .append ( user.login     );
            update_password .append ( user.password  );
            update_name     .append ( user.name      );
            update_isAdmin  .append ( user.isAdmin   );
            update_isActive .append ( user.isActive  );
        }
    }

    insertQuery.bindValue(":userid",    insert_userId   );
    insertQuery.bindValue(":login",     insert_login    );
    insertQuery.bindValue(":password",  insert_password );
    insertQuery.bindValue(":name",      insert_name     );
    insertQuery.bindValue(":isadmin",   insert_isAdmin  );
    insertQuery.bindValue(":isactive",  insert_isActive );

    updateQuery.bindValue(":userid",    update_userId   );
    updateQuery.bindValue(":login",     update_login    );
    updateQuery.bindValue(":password",  update_password );
    updateQuery.bindValue(":name",      update_name     );
    updateQuery.bindValue(":isadmin",   update_isAdmin  );
    updateQuery.bindValue(":isactive",  update_isActive );

    bool queryResult = true;
    if (!update_userId.isEmpty())
        queryResult = _db->getResult(updateQuery, true);
    if (queryResult && !insert_userId.isEmpty())
    {
        queryResult = _db->getResult(insertQuery, true);
    }

    return queryResult;
}
