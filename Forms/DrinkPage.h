#ifndef DRINKPAGE_H
#define DRINKPAGE_H

#include <QWidget>
#include <QPointer>
#include "ItemPage.h"
#include <Models/DrinksPageModel.h>

class DrinkPage : public ItemPage
{
public:
    DrinkPage(QWidget *parent = 0);
    ~DrinkPage();

protected slots:
    void addItem();
    void removeItem();

    void save();
    void cancel();

private:
    QPointer<DrinksPageModel> _model;
};

#endif // DRINKPAGE_H
