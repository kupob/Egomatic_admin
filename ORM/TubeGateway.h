#ifndef TUBEGATEWAY_H
#define TUBEGATEWAY_H

#include <QObject>

#include "../Utils/DbAdapter.h"
#include "Tube.h"

class TubeGateway
{
public:
    TubeGateway();

    bool getTubes(QList<Tube> &data);
    bool saveTubes(QList<Tube> data);

private:
    DbAdapter* _db;
};

#endif // TUBEGATEWAY_H
