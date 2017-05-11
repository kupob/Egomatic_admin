#include "DevicePage.h"
#include "ui_ItemPage.h"
#include <Utils/DbAdapter.h>
#include <ORM/DeviceGateway.h>

DevicePage::DevicePage(QWidget *parent) :
    ItemPage(parent)
{
    _model = QPointer<DevicePageModel>(new DevicePageModel(this));
    ui->tableView->setModel(_model.data());
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
    QList<Device> devices = _model->getDevices();
    DeviceGateway deviceGateway;

    bool ok = false;
    if (!devices.isEmpty())
        ok = deviceGateway.saveDevices(devices);

    if (ok)
        _model->resetData();
}

void DevicePage::cancel()
{
    _model->resetData();
}
