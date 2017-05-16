#include "DrinkGateway.h"
#include <QSqlQuery>
#include <QDebug>

DrinkGateway::DrinkGateway()
{
    _db = DbAdapter::instance();
}

bool DrinkGateway::getItems(QList<Drink> &data)
{
    QSqlQuery query = _db->getQuery();

    query.prepare("SELECT drinkid, name, cost, abv, ibu, description, isactive FROM public.em_drink WHERE isactive = true");

    QList<QList<QVariant> > rawData;
    bool queryResult = _db->getResult(query, rawData);
    data = Drink::convertFromData(rawData);

    return queryResult && !data.isEmpty();
}

bool DrinkGateway::saveItems(QList<Drink> data)
{
    QSqlQuery selectQuery = _db->getQuery();
    QSqlQuery insertQuery = _db->getQuery();
    QSqlQuery updateQuery = _db->getQuery();

    QStringList existsIdList;
    selectQuery.prepare("SELECT DISTINCT drinkid FROM em_drink; ");
    bool result = _db->getResult(selectQuery, existsIdList);

    insertQuery.prepare(" INSERT INTO em_drink("
                  " drinkid, name, cost, abv, ibu, description, isactive)"
                  " VALUES (:drinkid, :name, :cost, :abv, :ibu, :description, :isactive)"
                  " ON CONFLICT (drinkid) DO NOTHING ;");

    updateQuery.prepare(" UPDATE em_drink"
                        " SET name=:name, cost=:cost, abv=:abv, ibu=:ibu, description=:description, isactive=:isactive "
                        " WHERE drinkid=:drinkid;");

    QVariantList insert_drinkIds,
                 insert_names,
                 insert_costs,
                 insert_abvs,
                 insert_ibus,
                 insert_descriptions,
                 insert_isActives;

    QVariantList update_drinkIds,
                 update_names,
                 update_costs,
                 update_abvs,
                 update_ibus,
                 update_descriptions,
                 update_isActives;


    foreach (Drink drink, data)
    {
        if (!existsIdList.contains(drink.drinkId))
        {
            insert_drinkIds     .append ( drink.drinkId     );
            insert_names        .append ( drink.name        );
            insert_costs        .append ( drink.cost        );
            insert_abvs         .append ( drink.abv         );
            insert_ibus         .append ( drink.ibu         );
            insert_descriptions .append ( drink.description );
            insert_isActives    .append ( drink.isActive    );
        }
        else
        {
            update_drinkIds     .append ( drink.drinkId     );
            update_names        .append ( drink.name        );
            update_costs        .append ( drink.cost        );
            update_abvs         .append ( drink.abv         );
            update_ibus         .append ( drink.ibu         );
            update_descriptions .append ( drink.description );
            update_isActives    .append ( drink.isActive    );
        }
    }

    insertQuery.bindValue(":drinkid",     insert_drinkIds    );
    insertQuery.bindValue(":name",        insert_names       );
    insertQuery.bindValue(":cost",        insert_costs       );
    insertQuery.bindValue(":abv",         insert_abvs        );
    insertQuery.bindValue(":ibu",         insert_ibus        );
    insertQuery.bindValue(":description", insert_descriptions);
    insertQuery.bindValue(":isactive",    insert_isActives   );

    updateQuery.bindValue(":drinkid",     update_drinkIds    );
    updateQuery.bindValue(":name",        update_names       );
    updateQuery.bindValue(":cost",        update_costs       );
    updateQuery.bindValue(":abv",         update_abvs        );
    updateQuery.bindValue(":ibu",         update_ibus        );
    updateQuery.bindValue(":description", update_descriptions);
    updateQuery.bindValue(":isactive",    update_isActives   );

    bool queryResult = true;
    if (!update_drinkIds.isEmpty())
        queryResult = _db->getResult(updateQuery, true);
    if (queryResult && !insert_drinkIds.isEmpty())
    {
        queryResult = _db->getResult(insertQuery, true);
    }

    return queryResult;
}
