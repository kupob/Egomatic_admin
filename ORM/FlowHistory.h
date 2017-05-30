#ifndef FLOWHISTORY_H
#define FLOWHISTORY_H

#include <QString>
#include <QList>
#include <QVariant>
#include <QDateTime>

class FlowHistory
{
public:
    FlowHistory()
    {
        amount = 0.f;
        spent = 0.f;
        isActive = true;
    }

    bool isValid() { return !flowHistoryId.isEmpty(); }

    QString     flowHistoryId;  //  flowhistoryid uuid NOT NULL, -- Идентификатор записи
    QDateTime   flowTime;       //  flowtime timestamp without time zone, -- Дата и время налива напитка
    QString     drinkId;        //  drinkid uuid, -- Идентификатор напитка
    float       amount;         //  amount real DEFAULT 0.0, -- Налитый объем
    float       spent;          //  spent real DEFAULT 0.0, -- Уплаченная стоимость
    QString     customerId;     //  customerid uuid, -- Идентификатор клиента
    bool        isActive;       //  isactive boolean DEFAULT true, -- Флаг активности

    static const int fieldCount = 7;
    static const int columnCount = 5;

public:
    QVariant data(int position) const
    {
        switch (position) {
        case 0:     return QVariant::fromValue(flowTime);
        case 1:     return QVariant::fromValue(customerId);
        case 2:     return QVariant::fromValue(drinkId);
        case 3:     return QVariant::fromValue(QString::number(amount, 'f', 2) + " л.");
        case 4:     return QVariant::fromValue(QString::number(spent, 'f', 2) + " р.");
        default:    return QVariant();
        }
    }

    static QVariant headerData(int position)
    {
        switch (position) {
        case 0:     return QString("Дата и время");
        case 1:     return QString("Посетитель");
        case 2:     return QString("Напиток");
        case 3:     return QString("Объем");
        case 4:     return QString("Стоимость");
        default:    return QVariant();
        }
    }

    static QList<FlowHistory> convertFromData(QList< QList<QVariant> > data)
    {
        QList<FlowHistory> result;

        foreach (auto singleData, data)
        {
            Q_ASSERT(singleData.size() == fieldCount);

            FlowHistory flowHistory;
            flowHistory.flowHistoryId = singleData.value(0).toString();
            flowHistory.flowTime      = singleData.value(1).toDateTime();
            flowHistory.drinkId       = singleData.value(2).toString();
            flowHistory.amount        = singleData.value(3).toFloat();
            flowHistory.spent         = singleData.value(4).toFloat();
            flowHistory.customerId    = singleData.value(5).toString();
            flowHistory.isActive      = singleData.value(6).toBool();

            result.append(flowHistory);
        }

        return result;
    }
};

#endif // FLOWHISTORY_H
