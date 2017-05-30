#include "MainWindow.h"
#include "ui_mainwindow.h"
#include <Forms/ItemPage.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
//    ItemPage* itemPage = new ItemPage(this);
//    ui->stackedWidget->insertWidget(1, itemPage);

    ui->backButton->setEnabled(false);
    ui->buttonGroup->setId(ui->backButton, 0);
    ui->buttonGroup->setId(ui->drinksButton, 1);
    ui->buttonGroup->setId(ui->equipmentButton, 2);
    ui->buttonGroup->setId(ui->statsButton, 3);

    connect(ui->buttonGroup, SIGNAL(buttonClicked(int)), ui->stackedWidget, SLOT(setCurrentIndex(int)));
    connect(ui->buttonGroup, SIGNAL(buttonClicked(int)), this, SLOT(setHeader()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setHeader()
{
    QAbstractButton* currentPageButton = ui->buttonGroup->button(ui->stackedWidget->currentIndex());
    QString text = currentPageButton->text();

    if (ui->stackedWidget->currentIndex() == 0)
    {
        ui->backButton->setEnabled(false);
        text = QString("Главное меню");
    }
    else
        ui->backButton->setEnabled(true);

    ui->titleLabel->setText(text);
}
