#ifndef TUBEGATEWAY_H
#define TUBEGATEWAY_H

#include <QObject>

#include "../Utils/DbAdapter.h"
#include "Tube.h"

class TubeGateway
{
public:
    TubeGateway();

    bool getItems(QList<Tube> &data);
    bool saveItems(QList<Tube> data);

private:
    bool saveTubeSettings(QList<Tube> data);
    DbAdapter* _db;
};

#endif // TUBEGATEWAY_H
