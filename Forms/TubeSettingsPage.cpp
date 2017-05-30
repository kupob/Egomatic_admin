#include "TubeSettingsPage.h"
#include "ui_ItemPage.h"
#include <Utils/DbAdapter.h>
#include <ORM/TubeSettingsGateway.h>
#include <Models/DrinkComboboxDelegate.h>

TubeSettingsPage::TubeSettingsPage(QWidget *parent) :
    ItemPage(parent)
{
    _model = QPointer<TubeSettingsPageModel>(new TubeSettingsPageModel(this));
    ui->tableView->setModel(_model.data());
    ui->tableView->resizeColumnsToContents();

    DrinkComboboxDelegate* delegate = new DrinkComboboxDelegate(this);
    ui->tableView->setItemDelegateForColumn(1, delegate);

    ui->addButton->hide();
    ui->removeButton->hide();
}

TubeSettingsPage::~TubeSettingsPage()
{

}

void TubeSettingsPage::save()
{
    QList<TubeSettings> items = _model->getItems();
    TubeSettingsGateway gateway;

    bool ok = false;
    if (!items.isEmpty())
    {
        for (int i = 0; i < items.count(); i++)
        {
            if (!items.at(i).isValid())
                items[i].tubeSettingsId = DbAdapter::instance()->getUuid();
        }

        ok = gateway.saveItems(items);
    }

    if (ok)
        _model->resetData();
}

void TubeSettingsPage::cancel()
{
    _model->resetData();
}
