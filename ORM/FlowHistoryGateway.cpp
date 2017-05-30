#include "FlowHistoryGateway.h"
#include <QSqlQuery>
#include <QDebug>

FlowHistoryGateway::FlowHistoryGateway()
{
    _db = DbAdapter::instance();
}

bool FlowHistoryGateway::getItems(QList<FlowHistory> &data)
{
    QSqlQuery query = _db->getQuery();

    query.prepare("SELECT flowhistoryid, flowtime, drinkid, amount, spent, customerid, isactive "
                  "FROM public.stat_flowhistory WHERE isactive = true; ");

    QList<QList<QVariant> > rawData;
    bool queryResult = _db->getResult(query, rawData);
    data = FlowHistory::convertFromData(rawData);

    return queryResult && !data.isEmpty();
}
