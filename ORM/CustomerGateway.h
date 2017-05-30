#ifndef CUSTOMERGATEWAY_H
#define CUSTOMERGATEWAY_H

#include <QObject>

#include "../Utils/DbAdapter.h"
#include "Customer.h"

class CustomerGateway
{
public:
    CustomerGateway();

    bool getItems(QList<Customer> &data);
    bool saveItems(QList<Customer> data);

private:
    DbAdapter* _db;
};

#endif // CUSTOMERGATEWAY_H
