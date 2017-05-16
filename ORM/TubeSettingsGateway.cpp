#include "TubeSettingsGateway.h"
#include <QSqlQuery>
#include <QDebug>

TubeSettingsGateway::TubeSettingsGateway()
{
    _db = DbAdapter::instance();
}

bool TubeSettingsGateway::getItems(QList<TubeSettings> &data)
{
    QSqlQuery query = _db->getQuery();

    query.prepare(" SELECT tubesettingsid, tubeid, drinkid, t.number, isundermaintenance, COALESCE(ts.isactive, true) "
                  " FROM em_tube t"
                  " LEFT JOIN lnk_tubesettings ts USING (tubeid) "
                  " WHERE (ts.isactive IS NULL OR ts.isactive = true) AND t.isactive = true; ");

    QList<QList<QVariant> > rawData;
    bool queryResult = _db->getResult(query, rawData);
    data = TubeSettings::convertFromData(rawData);

    return queryResult && !data.isEmpty();
}

bool TubeSettingsGateway::saveItems(QList<TubeSettings> data)
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
                  " ON CONFLICT (tubesettingsid) DO NOTHING ;");

    updateQuery.prepare(" UPDATE lnk_tubesettings"
                        " SET tubeid=:tubeid, drinkid=:drinkid, isundermaintenance=:isundermaintenance, isactive=:isactive "
                        " WHERE tubesettingsid=:tubesettingsid; ");

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


    foreach (TubeSettings tube, data)
    {
        if (tube.drinkId.isEmpty())
            tube.drinkId = QString();

        if (!existsIdList.contains(tube.tubeId))
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
