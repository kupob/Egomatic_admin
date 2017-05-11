#ifndef DEVICEGATEWAY_H
#define DEVICEGATEWAY_H

#include <QObject>

#include "../Utils/DbAdapter.h"
#include "Device.h"

class DeviceGateway
{
public:
    DeviceGateway();

    bool getDevices(QList<Device> &data);
    bool saveDevices(QList<Device> data);

private:
    DbAdapter* _db;
};

#endif // DEVICEGATEWAY_H
