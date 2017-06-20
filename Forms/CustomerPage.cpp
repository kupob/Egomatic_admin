#include "CustomerPage.h"
#include "ui_ItemPage.h"
#include <Utils/DbAdapter.h>
#include <ORM/CustomerGateway.h>

CustomerPage::CustomerPage(QWidget *parent) :
    ItemPage(parent)
{
    _model = QPointer<CustomerPageModel>(new CustomerPageModel(this));
    ui->tableView->setModel(_model.data());
    ui->tableView->resizeColumnsToContents();
}

CustomerPage::~CustomerPage()
{

}

void CustomerPage::addItem()
{
    Customer customer;
    customer.customerId = DbAdapter::instance()->getUuid();
    _model->addItem(customer);
}

void CustomerPage::removeItem()
{
    QModelIndex current = ui->tableView->currentIndex();
    _model->removeItem(current);
}

void CustomerPage::save()
{
    QList<Customer> items = _model->getItems();
    CustomerGateway customerGateway;

    bool ok = false;
    if (!items.isEmpty())
        ok = customerGateway.saveItems(items);

    if (ok)
        _model->resetData();
}

void CustomerPage::cancel()
{
    _model->resetData();
}
