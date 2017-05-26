#ifndef FLOWHISTORYGATEWAY_H
#define FLOWHISTORYGATEWAY_H

#include <QObject>

#include "../Utils/DbAdapter.h"
#include "FlowHistory.h"

class FlowHistoryGateway
{
public:
    FlowHistoryGateway();

    bool getItems(QList<FlowHistory> &data);

private:
    DbAdapter* _db;
};

#endif // FLOWHISTORYGATEWAY_H
