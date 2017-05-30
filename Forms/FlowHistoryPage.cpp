#include "FlowHistoryPage.h"
#include "ui_ItemPage.h"
#include <Utils/DbAdapter.h>
#include <ORM/FlowHistoryGateway.h>

FlowHistoryPage::FlowHistoryPage(QWidget *parent) :
    ItemPage(parent)
{
    _model = QPointer<FlowHistoryPageModel>(new FlowHistoryPageModel(this));
    ui->tableView->setModel(_model.data());
    ui->tableView->resizeColumnsToContents();

    ui->addButton->hide();
    ui->removeButton->hide();
    ui->saveButton->hide();
    ui->cancelButton->setText("Обновить");
}

FlowHistoryPage::~FlowHistoryPage()
{

}
