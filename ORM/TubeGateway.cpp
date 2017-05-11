#include "TubeGateway.h"
#include <QSqlQuery>
#include <QDebug>

TubeGateway::TubeGateway()
{
    _db = DbAdapter::instance();
}

bool TubeGateway::getTubes(QList<Tube> &data)
{
    QSqlQuery query = _db->getQuery();

    query.prepare("SELECT tubeid, number, isactive FROM em_tube WHERE isactive = true;");

    QList<QList<QVariant> > rawData;
    bool queryResult = _db->getResult(query, rawData);
    data = Tube::convertFromData(rawData);

    return queryResult && !data.isEmpty();
}

bool TubeGateway::saveTubes(QList<Tube> data)
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

    return result;
}
