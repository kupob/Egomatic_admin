#ifndef CONTROLLERPAGE_H
#define CONTROLLERPAGE_H

#include <QWidget>
#include <QPointer>
#include "ItemPage.h"
#include <Models/ControllerPageModel.h>

class ControllerPage : public ItemPage
{
public:
    ControllerPage(QWidget *parent = 0);
    ~ControllerPage();

protected slots:
    void addItem();
    void removeItem();

    void save();
    void cancel();

private:
    QPointer<ControllerPageModel> _model;
};

#endif // CONTROLLERPAGE_H
