#include "DrinkPage.h"
#include "ui_ItemPage.h"
#include <Utils/DbAdapter.h>
#include <ORM/DrinkGateway.h>

DrinkPage::DrinkPage(QWidget *parent) :
    ItemPage(parent)
{
    _model = QPointer<DrinksPageModel>(new DrinksPageModel(this));
    ui->tableView->setModel(_model.data());
    ui->tableView->resizeColumnsToContents();
}

DrinkPage::~DrinkPage()
{

}

void DrinkPage::addItem()
{
    Drink drink;
    drink.drinkId = DbAdapter::instance()->getUuid();
    _model->addItem(drink);
}

void DrinkPage::removeItem()
{
    QModelIndex current = ui->tableView->currentIndex();
    _model->removeItem(current);
}

void DrinkPage::save()
{
    QList<Drink> drinks = _model->getItems();
    DrinkGateway drinkGateway;

    bool ok = false;
    if (!drinks.isEmpty())
        ok = drinkGateway.saveItems(drinks);

    if (ok)
        _model->resetData();
}

void DrinkPage::cancel()
{
    _model->resetData();
}
