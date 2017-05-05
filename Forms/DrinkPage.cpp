#include "DrinkPage.h"
#include "ui_ItemPage.h"
#include <Utils/DbAdapter.h>

DrinkPage::DrinkPage(QWidget *parent) :
    ItemPage(parent)
{
    _model = QPointer<DrinksPageModel>(new DrinksPageModel(this));
    ui->tableView->setModel(_model.data());
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

}

void DrinkPage::cancel()
{

}
