#include "MainWindow.h"
#include "LoginDialog.h"
#include "DbAdapter.h"
#include "ConfigReader.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // добавляем в пути поиска ./sqldrivers
    QStringList pathList = a.libraryPaths();
    pathList.append(a.applicationDirPath() +"/sqldrivers");
    a.setLibraryPaths(pathList);

    ConfigReader configReader;

    DbAdapter *dbAdapter = DbAdapter::instance();
    bool connectionOpened = dbAdapter->createConnection(
                configReader.dbHost(),
                configReader.dbName(),
                configReader.dbUser(),
                configReader.dbPassword(),
                configReader.dbPort());

    qDebug() << connectionOpened;

    LoginDialog loginDialog;
    loginDialog.show();

    MainWindow mainWindow;
    mainWindow.show();
    mainWindow.hide();

    a.connect(&loginDialog, SIGNAL(authSuccess()), &mainWindow, SLOT(show()));

    return a.exec();
}
