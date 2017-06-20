#ifndef CONTROLLERGATEWAY_H
#define CONTROLLERGATEWAY_H

#include <QObject>

#include "../Utils/DbAdapter.h"
#include "Controller.h"

class ControllerGateway
{
public:
    ControllerGateway();

    bool getControllers(QList<Controller> &data);
    bool saveItems(QList<Controller> data);

private:
    DbAdapter* _db;
};


#endif // CONTROLLERGATEWAY_H
