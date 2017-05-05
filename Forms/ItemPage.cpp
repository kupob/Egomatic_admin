#include "ItemPage.h"
#include "ui_ItemPage.h"

ItemPage::ItemPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ItemPage)
{
    ui->setupUi(this);

    connect(ui->addButton, SIGNAL(clicked()), this, SLOT(addItem()));
    connect(ui->removeButton, SIGNAL(clicked()), this, SLOT(removeItem()));
    connect(ui->saveButton, SIGNAL(clicked()), this, SLOT(save()));
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(cancel()));
}

ItemPage::~ItemPage()
{
    delete ui;
}

void ItemPage::addItem()
{

}

void ItemPage::removeItem()
{

}

void ItemPage::save()
{

}

void ItemPage::cancel()
{

}
