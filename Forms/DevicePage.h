#ifndef DEVICEPAGE_H
#define DEVICEPAGE_H

#include <QWidget>
#include <QPointer>
#include "ItemPage.h"
#include <Models/DevicePageModel.h>

class DevicePage : public ItemPage
{
public:
    DevicePage(QWidget *parent = 0);
    ~DevicePage();

protected slots:
    void addItem();
    void removeItem();

    void save();
    void cancel();

private:
    QPointer<DevicePageModel> _model;
};

#endif // DEVICEPAGE_H
