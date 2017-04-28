#include "LoginDialog.h"
#include "ui_LoginDialog.h"

#include "DbAdapter.h"
#include <QCryptographicHash>
#include <QMessageBox>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent/*, Qt::FramelessWindowHint*/),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

    connect(ui->loginButton, &QPushButton::clicked, this, &LoginDialog::checkAuth);
    connect(ui->cancelButton, &QPushButton::clicked, this, &QWidget::close);
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
    bool ok = db->getResult(QString("SELECT userid FROM sys_user WHERE login = '%1' AND password = '%2' LIMIT 1;").arg(userName, passwordEncr));

    if (ok)
        emit authSuccess();
    else
    {
        emit authFailed();
        QMessageBox::warning(this, tr("Авторизация"), tr("Неверное имя пользователя или пароль"));
    }
}
