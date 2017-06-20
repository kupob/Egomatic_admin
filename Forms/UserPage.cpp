#include "UserPage.h"
#include "ui_ItemPage.h"
#include <Utils/DbAdapter.h>
#include <ORM/UserGateway.h>

UserPage::UserPage(QWidget *parent) :
    ItemPage(parent)
{
    _model = QPointer<UserPageModel>(new UserPageModel(this));
    ui->tableView->setModel(_model.data());
    ui->tableView->resizeColumnsToContents();
}

UserPage::~UserPage()
{

}

void UserPage::addItem()
{
    User user;
    user.userId = DbAdapter::instance()->getUuid();
    _model->addItem(user);
}

void UserPage::removeItem()
{
    QModelIndex current = ui->tableView->currentIndex();
    _model->removeItem(current);
}

void UserPage::save()
{
    QList<User> items = _model->getItems();
    UserGateway userGateway;

    bool ok = false;
    if (!items.isEmpty())
        ok = userGateway.saveItems(items);

    if (ok)
        _model->resetData();
}

void UserPage::cancel()
{
    _model->resetData();
}
