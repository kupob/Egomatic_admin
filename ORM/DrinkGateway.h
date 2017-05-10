#ifndef DRINKGATEWAY_H
#define DRINKGATEWAY_H

#include <QObject>

#include "../Utils/DbAdapter.h"
#include "Drink.h"

class DrinkGateway
{
public:
    DrinkGateway();

    bool getDrinks(QList<Drink> &data);
    bool saveDrinks(QList<Drink> data);

private:
    DbAdapter* _db;
};

#endif // DRINKGATEWAY_H
