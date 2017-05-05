#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "LoginDialog.h"

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    LoginDialog* _loginDialog;
};

#endif // MAINWINDOW_H
