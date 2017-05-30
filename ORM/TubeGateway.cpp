#include "TubeGateway.h"
#include <QSqlQuery>
#include <QDebug>

TubeGateway::TubeGateway()
{
    _db = DbAdapter::instance();
}

bool TubeGateway::getItems(QList<Tube> &data)
{
    QSqlQuery query = _db->getQuery();

    query.prepare(" SELECT e_t.tubeid, e_t.number, ts.tubesettingsid, ts.drinkid, "
                  " COALESCE(ts.isundermaintenance, false), e_t.isactive "
                  " FROM em_tube e_t "
                  " LEFT JOIN lnk_tubesettings ts USING (tubeid) "
                  " WHERE e_t.isactive = true; ");

    QList<QList<QVariant> > rawData;
    bool queryResult = _db->getResult(query, rawData);
    data = Tube::convertFromData(rawData);

    return queryResult && !data.isEmpty();
}

bool TubeGateway::saveItems(QList<Tube> data)
{
    QSqlQuery selectQuery = _db->getQuery();
    QSqlQuery insertQuery = _db->getQuery();
    QSqlQuery updateQuery = _db->getQuery();

    QStringList existsIdList;
    selectQuery.prepare("SELECT DISTINCT tubeid FROM em_tube; ");
    _db->getResult(selectQuery, existsIdList);

    insertQuery.prepare(" INSERT INTO em_tube("
                  " tubeid, number, isactive)"
                  " VALUES (:tubeid, :number, :isactive)"
                  " ON CONFLICT (tubeid) DO NOTHING ;");

    updateQuery.prepare(" UPDATE em_tube"
                        " SET number=:number, isactive=:isactive "
                        " WHERE tubeid=:tubeid;");

    QVariantList insert_tubeIds,
                 insert_numbers,
                 insert_isActives;

    QVariantList update_tubeIds,
                 update_numbers,
                 update_isActives;


    foreach (Tube tube, data)
    {
        if (!existsIdList.contains(tube.tubeId))
        {
            insert_tubeIds .append ( tube.tubeId  );
            insert_numbers     .append ( tube.number       );
            insert_isActives     .append ( tube.isActive      );
        }
        else
        {
            update_tubeIds .append ( tube.tubeId  );
            update_numbers     .append ( tube.number       );
            update_isActives     .append ( tube.isActive      );
        }
    }

    bool result = true;
    if (!update_tubeIds.isEmpty())
    {
        updateQuery.bindValue(":tubeid", update_tubeIds );
        updateQuery.bindValue(":number",      update_numbers     );
        updateQuery.bindValue(":isactive",     update_isActives     );
        result &= _db->getResult(updateQuery, true);
    }
    if (!insert_tubeIds.isEmpty())
    {
        insertQuery.bindValue(":tubeid", insert_tubeIds );
        insertQuery.bindValue(":number",      insert_numbers     );
        insertQuery.bindValue(":isactive",     insert_isActives     );
        result &= _db->getResult(insertQuery, true);
    }

    return result && saveTubeSettings(data);
}

bool TubeGateway::saveTubeSettings(QList<Tube> data)
{
    QSqlQuery selectQuery = _db->getQuery();
    QSqlQuery insertQuery = _db->getQuery();
    QSqlQuery updateQuery = _db->getQuery();

    QStringList existsIdList;
    selectQuery.prepare("SELECT DISTINCT tubesettingsid FROM lnk_tubesettings; ");
    _db->getResult(selectQuery, existsIdList);

    insertQuery.prepare(" INSERT INTO lnk_tubesettings("
                  " tubesettingsid, tubeid, drinkid, isundermaintenance, isactive)"
                  " VALUES (:tubesettingsid, :tubeid, :drinkid, :isundermaintenance, :isactive)"
                  " ON CONFLICT (tubesettingsid) DO NOTHING ;"
                  " NOTIFY tube_maintenance; ");

    updateQuery.prepare(" UPDATE lnk_tubesettings"
                        " SET tubeid=:tubeid, drinkid=:drinkid, isundermaintenance=:isundermaintenance, isactive=:isactive "
                        " WHERE tubesettingsid=:tubesettingsid; "
                        " NOTIFY tube_maintenance; ");

    QVariantList insert_tubeSettingsId,
                 insert_tubeId,
                 insert_drinkId,
                 insert_isUnderMaintenance,
                 insert_isActive;

    QVariantList update_tubeSettingsId,
                 update_tubeId,
                 update_drinkId,
                 update_isUnderMaintenance,
                 update_isActive;


    foreach (Tube tube, data)
    {
        if (tube.drinkId.isEmpty())
            tube.drinkId = QString();

        if (!existsIdList.contains(tube.tubeSettingsId))
        {
            insert_tubeSettingsId     . append ( tube.tubeSettingsId     );
            insert_tubeId             . append ( tube.tubeId             );
            insert_drinkId            . append ( tube.drinkId            );
            insert_isUnderMaintenance . append ( tube.isUnderMaintenance );
            insert_isActive           . append ( tube.isActive           );
        }
        else
        {
            update_tubeSettingsId     . append ( tube.tubeSettingsId     );
            update_tubeId             . append ( tube.tubeId             );
            update_drinkId            . append ( tube.drinkId            );
            update_isUnderMaintenance . append ( tube.isUnderMaintenance );
            update_isActive           . append ( tube.isActive           );
        }
    }

    bool result = true;
    if (!update_tubeSettingsId.isEmpty())
    {
        updateQuery.bindValue(":tubesettingsid"     , update_tubeSettingsId     );
        updateQuery.bindValue(":tubeid"             , update_tubeId             );
        updateQuery.bindValue(":drinkid"            , update_drinkId            );
        updateQuery.bindValue(":isundermaintenance" , update_isUnderMaintenance );
        updateQuery.bindValue(":isactive"           , update_isActive           );

        result &= _db->getResult(updateQuery, true);
    }
    if (!insert_tubeSettingsId.isEmpty())
    {
        insertQuery.bindValue(":tubesettingsid"     , insert_tubeSettingsId     );
        insertQuery.bindValue(":tubeid"             , insert_tubeId             );
        insertQuery.bindValue(":drinkid"            , insert_drinkId            );
        insertQuery.bindValue(":isundermaintenance" , insert_isUnderMaintenance );
        insertQuery.bindValue(":isactive"           , insert_isActive           );

        result &= _db->getResult(insertQuery, true);
    }

    return result;
}
