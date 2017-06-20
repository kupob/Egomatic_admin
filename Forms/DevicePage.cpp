#include "DevicePage.h"
#include "ui_ItemPage.h"
#include <Utils/DbAdapter.h>
#include <ORM/DeviceGateway.h>
#include <Models/DeviceTypeDelegate.h>

DevicePage::DevicePage(QWidget *parent) :
    ItemPage(parent)
{
    _model = QPointer<DevicePageModel>(new DevicePageModel(this));
    ui->tableView->setModel(_model.data());
    ui->tableView->resizeColumnsToContents();

    DeviceTypeDelegate* delegate = new DeviceTypeDelegate(this);
    ui->tableView->setItemDelegateForColumn(1, delegate);
}

DevicePage::~DevicePage()
{

}

void DevicePage::addItem()
{
    Device device;
    device.deviceId = DbAdapter::instance()->getUuid();
    _model->addItem(device);
}

void DevicePage::removeItem()
{
    QModelIndex current = ui->tableView->currentIndex();
    _model->removeItem(current);
}

void DevicePage::save()
{
    QList<Device> items = _model->getDevices();
    DeviceGateway deviceGateway;

    bool ok = false;
    if (!items.isEmpty())
        ok = deviceGateway.saveItems(items);

    if (ok)
        _model->resetData();
}

void DevicePage::cancel()
{
    _model->resetData();
}
