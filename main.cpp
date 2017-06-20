#include "Forms/MainWindow.h"
#include "Forms/LoginDialog.h"
#include "Utils/DbAdapter.h"
#include "Utils/ConfigReader.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // добавляем в пути поиска ./sqldrivers
    QStringList pathList = a.libraryPaths();
    pathList.append(a.applicationDirPath() +"/sqldrivers");
    a.setLibraryPaths(pathList);

    ConfigReader configReader;

    QFile qssFile("./Styles/style.qss");
    qssFile.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(qssFile.readAll());

    qApp->setStyleSheet(styleSheet);

    DbAdapter *dbAdapter = DbAdapter::instance();
    bool connectionOpened = dbAdapter->createConnection(
                configReader.dbHost(),
                configReader.dbName(),
                configReader.dbUser(),
                configReader.dbPassword(),
                configReader.dbPort());

    LoginDialog loginDialog;
    loginDialog.show();

    MainWindow mainWindow;
    mainWindow.show();
    mainWindow.hide();

    a.connect(&loginDialog, SIGNAL(authAsAdmin(bool)), &mainWindow, SLOT(showAsAdmin(bool)));
    a.connect(&loginDialog, SIGNAL(authSuccess()), &mainWindow, SLOT(show()));

    return a.exec();
}
