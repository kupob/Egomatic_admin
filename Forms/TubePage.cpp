#include "TubePage.h"
#include "ui_ItemPage.h"
#include <Utils/DbAdapter.h>
#include <ORM/TubeGateway.h>
#include <Models/DrinkComboboxDelegate.h>

TubePage::TubePage(QWidget *parent) :
    ItemPage(parent)
{
    _model = QPointer<TubePageModel>(new TubePageModel(this));
    ui->tableView->setModel(_model.data());
    ui->tableView->resizeColumnsToContents();

    DrinkComboboxDelegate* delegate = new DrinkComboboxDelegate(this);
    ui->tableView->setItemDelegateForColumn(1, delegate);
}

TubePage::~TubePage()
{

}

void TubePage::addItem()
{
    Tube tube;
    tube.tubeId = DbAdapter::instance()->getUuid();
    _model->addItem(tube);
}

void TubePage::removeItem()
{
    QModelIndex current = ui->tableView->currentIndex();
    _model->removeItem(current);
}

void TubePage::save()
{
    QList<Tube> items = _model->getItems();
    TubeGateway gateway;

    bool ok = false;
    if (!items.isEmpty())
    {
        for (int i = 0; i < items.count(); i++)
        {
            if (items.at(i).tubeSettingsId.isEmpty())
                items[i].tubeSettingsId = DbAdapter::instance()->getUuid();
        }

        ok = gateway.saveItems(items);
    }

    if (ok)
        _model->resetData();
}

void TubePage::cancel()
{
    _model->resetData();
}
