#include "DeviceGateway.h"
#include <QSqlQuery>
#include <QDebug>

DeviceGateway::DeviceGateway()
{
    _db = DbAdapter::instance();
}

bool DeviceGateway::getDevices(QList<Device> &data)
{
    QSqlQuery query = _db->getQuery();

    query.prepare("SELECT deviceid, pinnumber, devicetype, controllernumber, tubenumber, isactive FROM em_device WHERE isactive = true;");

    QList<QList<QVariant> > rawData;
    bool queryResult = _db->getResult(query, rawData);
    data = Device::convertFromData(rawData);

    return queryResult && !data.isEmpty();
}

bool DeviceGateway::saveItems(QList<Device> data)
{
    QSqlQuery selectQuery = _db->getQuery();
    QSqlQuery insertQuery = _db->getQuery();
    QSqlQuery updateQuery = _db->getQuery();

    QStringList existsIdList;
    selectQuery.prepare("SELECT DISTINCT deviceid FROM em_device; ");
    _db->getResult(selectQuery, existsIdList);

    insertQuery.prepare(" INSERT INTO em_device("
                  " deviceid, pinnumber, devicetype, controllernumber, tubenumber, isactive)"
                  " VALUES (:deviceid, :pinnumber, :devicetype, :controllernumber, :tubenumber, :isactive)"
                  " ON CONFLICT (deviceid) DO NOTHING ;");

    updateQuery.prepare(" UPDATE em_device"
                        " SET pinnumber=:pinnumber, devicetype=:devicetype, controllernumber=:controllernumber,"
                        " tubenumber=:tubenumber, isactive=:isactive "
                        " WHERE deviceid=:deviceid;");

    QVariantList
            insert_deviceId,
            insert_pinNumber,
            insert_deviceType,
            insert_controllerNumber,
            insert_tubeNumber,
            insert_isActive;

    QVariantList
            update_deviceId,
            update_pinNumber,
            update_deviceType,
            update_controllerNumber,
            update_tubeNumber,
            update_isActive;


    foreach (Device device, data)
    {
        if (!existsIdList.contains(device.deviceId))
        {
            insert_deviceId         .append ( device.deviceId         );
            insert_pinNumber        .append ( device.pinNumber        );
            insert_deviceType       .append ( device.deviceType       );
            insert_controllerNumber .append ( device.controllerNumber );
            insert_tubeNumber       .append ( device.tubeNumber       );
            insert_isActive         .append ( device.isActive         );
        }
        else
        {
            update_deviceId         .append ( device.deviceId         );
            update_pinNumber        .append ( device.pinNumber        );
            update_deviceType       .append ( device.deviceType       );
            update_controllerNumber .append ( device.controllerNumber );
            update_tubeNumber       .append ( device.tubeNumber       );
            update_isActive         .append ( device.isActive         );
        }
    }

    bool queryResult = true;
    if (!update_deviceId.isEmpty())
    {
        updateQuery.bindValue(":deviceid",         update_deviceId         );
        updateQuery.bindValue(":pinnumber",        update_pinNumber        );
        updateQuery.bindValue(":devicetype",       update_deviceType       );
        updateQuery.bindValue(":controllernumber", update_controllerNumber );
        updateQuery.bindValue(":tubenumber",       update_tubeNumber       );
        updateQuery.bindValue(":isactive",         update_isActive         );

        queryResult &= _db->getResult(updateQuery, true);
    }
    if (!insert_deviceId.isEmpty())
    {
        insertQuery.bindValue(":deviceid",         insert_deviceId         );
        insertQuery.bindValue(":pinnumber",        insert_pinNumber        );
        insertQuery.bindValue(":devicetype",       insert_deviceType       );
        insertQuery.bindValue(":controllernumber", insert_controllerNumber );
        insertQuery.bindValue(":tubenumber",       insert_tubeNumber       );
        insertQuery.bindValue(":isactive",         insert_isActive         );

        queryResult &= _db->getResult(insertQuery, true);
    }

    return queryResult;
}
