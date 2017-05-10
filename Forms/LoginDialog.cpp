#include "LoginDialog.h"
#include "ui_LoginDialog.h"

#include "../Utils/DbAdapter.h"
#include <QCryptographicHash>
#include <QMessageBox>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent/*, Qt::FramelessWindowHint*/),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

    connect(ui->loginButton, SIGNAL(clicked()), this, SLOT(checkAuth()));
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(close()));
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::checkAuth()
{
    QString userName = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();
    QString userNameEncr = QCryptographicHash::hash(userName.toUtf8(), QCryptographicHash::Md5).toHex();
    QString passwordEncr = QCryptographicHash::hash(userNameEncr.toUtf8() + password.toUtf8(), QCryptographicHash::Md5).toHex();

    DbAdapter *db = DbAdapter::instance();
    bool ok = db->tryLogin(userName, passwordEncr);

    if (ok)
    {
        emit authSuccess();
        close();
    }
    else
    {
        emit authFailed();
        QMessageBox::warning(this, tr("Авторизация"), tr("Неверное имя пользователя или пароль"));
    }
}
