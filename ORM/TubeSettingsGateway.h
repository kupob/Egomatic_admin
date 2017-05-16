#ifndef TUBESETTINGSGATEWAY_H
#define TUBESETTINGSGATEWAY_H

#include <QObject>

#include "../Utils/DbAdapter.h"
#include "TubeSettings.h"

class TubeSettingsGateway
{
public:
    TubeSettingsGateway();

    bool getItems(QList<TubeSettings> &data);
    bool saveItems(QList<TubeSettings> data);

private:
    DbAdapter* _db;
};

#endif // TUBESETTINGSGATEWAY_H
