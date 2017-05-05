#-------------------------------------------------
#
# Project created by QtCreator 2017-04-27T14:27:14
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Egomatic_admin
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SUBDIRS += \
    Forms \
    Utils

FORMS += \
    Forms/ItemPage.ui \
    Forms/LoginDialog.ui \
    Forms/MainWindow.ui

HEADERS += \
    Forms/ItemPage.h \
    Forms/LoginDialog.h \
    Forms/MainWindow.h \
    Utils/ConfigReader.h \
    Utils/DbAdapter.h \
    Models/DrinksPageModel.h \
    ORM/Drink.h \
    Forms/DrinkPage.h

SOURCES += \
    Forms/ItemPage.cpp \
    Forms/LoginDialog.cpp \
    Forms/MainWindow.cpp \
    Utils/ConfigReader.cpp \
    Utils/DbAdapter.cpp \
    main.cpp \
    Models/DrinksPageModel.cpp \
    Forms/DrinkPage.cpp



