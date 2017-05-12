#include "ControllerPage.h"
#include "ui_ItemPage.h"
#include <Utils/DbAdapter.h>
#include <ORM/ControllerGateway.h>

ControllerPage::ControllerPage(QWidget *parent) :
    ItemPage(parent)
{
    _model = QPointer<ControllerPageModel>(new ControllerPageModel(this));
    ui->tableView->setModel(_model.data());
    ui->tableView->resizeColumnsToContents();
}

ControllerPage::~ControllerPage()
{

}

void ControllerPage::addItem()
{
    Controller controller;
    controller.controllerId = DbAdapter::instance()->getUuid();
    _model->addItem(controller);
}

void ControllerPage::removeItem()
{
    QModelIndex current = ui->tableView->currentIndex();
    _model->removeItem(current);
}

void ControllerPage::save()
{
    QList<Controller> controllers = _model->getControllers();
    ControllerGateway controllerGateway;

    bool ok = false;
    if (!controllers.isEmpty())
        ok = controllerGateway.saveControllers(controllers);

    if (ok)
        _model->resetData();
}

void ControllerPage::cancel()
{
    _model->resetData();
}
