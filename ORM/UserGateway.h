#ifndef USERGATEWAY_H
#define USERGATEWAY_H

#include <QObject>

#include "../Utils/DbAdapter.h"
#include "User.h"

class UserGateway
{
public:
    UserGateway();

    bool getItems(QList<User> &data);
    bool saveItems(QList<User> data);

private:
    DbAdapter* _db;
};

#endif // USERGATEWAY_H
