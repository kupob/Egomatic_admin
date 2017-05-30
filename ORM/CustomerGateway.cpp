#include "CustomerGateway.h"
#include <QSqlQuery>
#include <QDebug>

CustomerGateway::CustomerGateway()
{
    _db = DbAdapter::instance();
}

bool CustomerGateway::getItems(QList<Customer> &data)
{
    QSqlQuery query = _db->getQuery();

    query.prepare("SELECT customerid, name, balance, totalspent, rfid, isactive FROM public.em_customer WHERE isactive = true");

    QList<QList<QVariant> > rawData;
    bool queryResult = _db->getResult(query, rawData);
    data = Customer::convertFromData(rawData);

    return queryResult && !data.isEmpty();
}

bool CustomerGateway::saveItems(QList<Customer> data)
{
    QSqlQuery selectQuery = _db->getQuery();
    QSqlQuery insertQuery = _db->getQuery();
    QSqlQuery updateQuery = _db->getQuery();

    QStringList existsIdList;
    selectQuery.prepare("SELECT DISTINCT customerid FROM em_customer; ");
    _db->getResult(selectQuery, existsIdList);

    insertQuery.prepare(" INSERT INTO em_customer("
                  " customerid, name, balance, totalspent, rfid, isactive)"
                  " VALUES (:customerid, :name, :balance, :totalspent, :rfid, :isactive)"
                  " ON CONFLICT (customerid) DO NOTHING ;");

    updateQuery.prepare(" UPDATE em_customer"
                        " SET name=:name, balance=:balance, totalspent=:totalspent, rfid=:rfid, isactive=:isactive "
                        " WHERE customerid=:customerid;");

    QVariantList insert_customerId,
                 insert_name,
                 insert_balance,
                 insert_totalSpent,
                 insert_rfid,
                 insert_isActive;

    QVariantList update_customerId,
                 update_name,
                 update_balance,
                 update_totalSpent,
                 update_rfid,
                 update_isActive;

    foreach (Customer customer, data)
    {
        if (!existsIdList.contains(customer.customerId))
        {
            insert_customerId  .append ( customer.customerId  );
            insert_name        .append ( customer.name        );
            insert_balance     .append ( customer.balance     );
            insert_totalSpent  .append ( customer.totalSpent  );
            insert_rfid        .append ( customer.rfid        );
            insert_isActive    .append ( customer.isActive    );
        }
        else
        {
            update_customerId  .append ( customer.customerId  );
            update_name        .append ( customer.name        );
            update_balance     .append ( customer.balance     );
            update_totalSpent  .append ( customer.totalSpent  );
            update_rfid        .append ( customer.rfid        );
            update_isActive    .append ( customer.isActive    );
        }
    }

    insertQuery.bindValue(":customerid",  insert_customerId  );
    insertQuery.bindValue(":name",        insert_name        );
    insertQuery.bindValue(":balance",     insert_balance     );
    insertQuery.bindValue(":totalspent",  insert_totalSpent  );
    insertQuery.bindValue(":rfid",        insert_rfid        );
    insertQuery.bindValue(":isactive",    insert_isActive    );

    updateQuery.bindValue(":customerid",  update_customerId  );
    updateQuery.bindValue(":name",        update_name        );
    updateQuery.bindValue(":balance",     update_balance     );
    updateQuery.bindValue(":totalspent",  update_totalSpent  );
    updateQuery.bindValue(":rfid",        update_rfid        );
    updateQuery.bindValue(":isactive",    update_isActive    );

    bool queryResult = true;
    if (!update_customerId.isEmpty())
        queryResult = _db->getResult(updateQuery, true);
    if (queryResult && !insert_customerId.isEmpty())
    {
        queryResult = _db->getResult(insertQuery, true);
    }

    return queryResult;
}
