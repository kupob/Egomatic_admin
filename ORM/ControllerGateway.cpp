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

    query.prepare("SELECT controllerid, address, macaddress, number, isactive FROM em_controller WHERE isactive = true;");

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
    _db->getResult(selectQuery, existsIdList);

    insertQuery.prepare(" INSERT INTO em_controller("
                  " controllerid, address, macaddress, number, isactive)"
                  " VALUES (:controllerid, :address, :macaddress, :number, :isactive)"
                  " ON CONFLICT (controllerid) DO NOTHING ;");

    updateQuery.prepare(" UPDATE em_controller"
                        " SET address=:address, macaddress=:macaddress, number=:number, isactive=:isactive "
                        " WHERE controllerid=:controllerid;");

    QVariantList insert_controllerIds,
                 insert_addresses,
                 insert_macaddresses,
                 insert_numbers,
                 insert_isActives;

    QVariantList update_controllerIds,
                 update_addresses,
                 update_macaddresses,
                 update_numbers,
                 update_isActives;


    foreach (Controller controller, data)
    {
        if (!existsIdList.contains(controller.controllerId))
        {
            insert_controllerIds .append ( controller.controllerId  );
            insert_addresses     .append ( controller.address       );
            insert_macaddresses  .append ( controller.macAddress    );
            insert_numbers       .append ( controller.number        );
            insert_isActives     .append ( controller.isActive      );
        }
        else
        {
            update_controllerIds .append ( controller.controllerId  );
            update_addresses     .append ( controller.address       );
            update_macaddresses  .append ( controller.macAddress    );
            update_numbers       .append ( controller.number        );
            update_isActives     .append ( controller.isActive      );
        }
    }

    bool queryResult = true;
    if (!update_controllerIds.isEmpty())
    {
        updateQuery.bindValue(":controllerid", update_controllerIds );
        updateQuery.bindValue(":address",      update_addresses     );
        updateQuery.bindValue(":macaddress",   update_macaddresses  );
        updateQuery.bindValue(":number",       update_numbers       );
        updateQuery.bindValue(":isactive",     update_isActives     );

        queryResult &= _db->getResult(updateQuery, true);
    }
    if (!insert_controllerIds.isEmpty())
    {
        insertQuery.bindValue(":controllerid", insert_controllerIds );
        insertQuery.bindValue(":address",      insert_addresses     );
        insertQuery.bindValue(":macaddress",   insert_macaddresses  );
        insertQuery.bindValue(":number",       insert_numbers       );
        insertQuery.bindValue(":isactive",     insert_isActives     );

        queryResult &= _db->getResult(insertQuery, true);
    }

    return queryResult;
}
