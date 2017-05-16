#ifndef DRINKGATEWAY_H
#define DRINKGATEWAY_H

#include <QObject>

#include "../Utils/DbAdapter.h"
#include "Drink.h"

class DrinkGateway
{
public:
    DrinkGateway();

    bool getItems(QList<Drink> &data);
    bool saveItems(QList<Drink> data);

private:
    DbAdapter* _db;
};

#endif // DRINKGATEWAY_H
