#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <QString>
#include <QList>
#include <QVariant>
#include <QDateTime>

class Customer
{
public:
    Customer()
    {
        balance = 0.f;
        totalSpent = 0.f;
        isActive = true;
    }

    bool isValid() { return !customerId.isEmpty(); }

    QString     customerId;     //  customerid uuid NOT NULL, -- Идентификатор клиента
    QString     name;           //  name character varying(256), -- Имя посетителя
    float       balance;        //  balance real DEFAULT 0.0, -- Текущий баланс
    float       totalSpent;     //  totalspent real DEFAULT 0.0, -- Всего потрачено
    quint64     rfid;           //  rfid bigint, -- Идентификатор RFID
    bool        isActive;       //  isactive boolean DEFAULT true, -- Флаг активности

    static const int fieldCount = 6;
    static const int columnCount = 4;

public:
    QVariant data(int position) const
    {
        switch (position) {
        case 0:     return QVariant::fromValue(name);
        case 1:     return QVariant::fromValue(balance);
        case 2:     return QVariant::fromValue(totalSpent);
        case 3:     return QVariant::fromValue(rfid);
        default:    return QVariant();
        }
    }

    static QVariant headerData(int position)
    {
        switch (position) {
        case 0:     return QString("Имя посетителя");
        case 1:     return QString("Текущий баланс");
        case 2:     return QString("Всего потрачено");
        case 3:     return QString("Идентификатор RFID");
        default:    return QVariant();
        }
    }

    static QList<Customer> convertFromData(QList< QList<QVariant> > data)
    {
        QList<Customer> result;

        foreach (auto singleData, data)
        {
            Q_ASSERT(singleData.size() == fieldCount);

            Customer customer;
            customer.customerId  = singleData.value(0).toString();
            customer.name        = singleData.value(1).toString();
            customer.balance     = singleData.value(2).toFloat();
            customer.totalSpent  = singleData.value(3).toFloat();
            customer.rfid        = singleData.value(4).toUInt();
            customer.isActive    = singleData.value(5).toBool();

            result.append(customer);
        }

        return result;
    }
};

#endif // CUSTOMER_H
