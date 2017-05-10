#include "ControllerGateway.h"
#include <QSqlQuery>
#include <QDebug>

ControllerGateway::ControllerGateway()
{
    _db = DbAdapter::instance();
}

bool ControllerGateway::getControllers(QList<Controller> &data)
{
    QSqlQuery query = _db->getQuery();

    query.prepare("SELECT controllerid, name, cost, abv, ibu, description, isactive FROM public.em_controller WHERE isactive = true");

    QList<QList<QVariant> > rawData;
    bool queryResult = _db->getResult(query, rawData);
    data = Controller::convertFromData(rawData);

    return queryResult && !data.isEmpty();
}

bool ControllerGateway::saveControllers(QList<Controller> data)
{
    QSqlQuery selectQuery = _db->getQuery();
    QSqlQuery insertQuery = _db->getQuery();
    QSqlQuery updateQuery = _db->getQuery();

    QStringList existsIdList;
    selectQuery.prepare("SELECT DISTINCT controllerid FROM em_controller; ");
    bool result = _db->getResult(selectQuery, existsIdList);

    insertQuery.prepare(" INSERT INTO em_controller("
                  " controllerid, address, macaddress, isactive)"
                  " VALUES (:controllerid, :address, :macaddress, :isactive)"
                  " ON CONFLICT (controllerid) DO NOTHING ;");

    updateQuery.prepare(" UPDATE em_controller"
                        " SET address=:address, macaddress=:macaddress, isactive=:isactive "
                        " WHERE controllerid=:controllerid;");

    QVariantList insert_controllerIds,
                 insert_addresses,
                 insert_macaddresses,
                 insert_isActives;

    QVariantList update_controllerIds,
                 update_addresses,
                 update_macaddresses,
                 update_isActives;


    foreach (Controller controller, data)
    {
        if (!existsIdList.contains(controller.controllerId))
        {
            insert_controllerIds .append ( controller.controllerId  );
            insert_addresses     .append ( controller.address       );
            insert_macaddresses  .append ( controller.macAddress    );
            insert_isActives     .append ( controller.isActive      );
        }
        else
        {
            update_controllerIds .append ( controller.controllerId  );
            update_addresses     .append ( controller.address       );
            update_macaddresses  .append ( controller.macAddress    );
            update_isActives     .append ( controller.isActive      );
        }
    }

    insertQuery.bindValue(":controllerid", insert_controllerIds );
    insertQuery.bindValue(":address",      insert_addresses     );
    insertQuery.bindValue(":macaddress",   insert_macaddresses  );
    insertQuery.bindValue(":isactive",     insert_isActives     );

    updateQuery.bindValue(":controllerid", update_controllerIds );
    updateQuery.bindValue(":address",      update_addresses     );
    updateQuery.bindValue(":macaddress",   update_macaddresses  );
    updateQuery.bindValue(":isactive",     update_isActives     );

    bool queryResult = true;
    if (!update_controllerIds.isEmpty())
        queryResult = _db->getResult(updateQuery, true);
    if (queryResult && !insert_controllerIds.isEmpty())
    {
        queryResult = _db->getResult(insertQuery, true);
    }

    return queryResult;
}
