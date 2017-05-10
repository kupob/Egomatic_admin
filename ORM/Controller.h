#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QString>
#include <QList>
#include <QVariant>

class Controller
{
public:
    Controller()
    {
        isActive = true;
    }

    bool isValid() { return !controllerId.isEmpty(); }

    QString controllerId; // controllerid uuid NOT NULL, -- Идентификатор напитка
    QString address;      // address inet, -- Адрес контроллера
    QString macAddress;   // macaddress macaddr, -- MAC адрес контроллера
    bool    isActive;     // boolean DEFAULT true, -- Флаг активности

    static const int fieldCount = 4;
    static const int columnCount = 2;

public:
    QVariant data(int position) const
    {
        switch (position) {
        case 0:     return QVariant::fromValue(address);
        case 1:     return QVariant::fromValue(macAddress);
        default:    return QVariant();
        }
    }

    void setData(int position, QVariant value)
    {
        switch (position) {
        case 0:
            address = value.toString();
            break;
        case 1:
            macAddress = value.toString();
            break;
        default:
            break;
        }
    }

    static QVariant headerData(int position)
    {
        switch (position) {
        case 0:     return QString("Адрес контроллера");
        case 1:     return QString("MAC адрес контроллера");
        default:    return QVariant();
        }
    }

    static QList<Controller> convertFromData(QList< QList<QVariant> > data)
    {
        QList<Controller> result;

        foreach (auto singleData, data)
        {
            Q_ASSERT(singleData.size() == fieldCount);

            Controller controller;
            controller.controllerId = singleData.value(0).toString();
            controller.address      = singleData.value(1).toString();
            controller.macAddress   = singleData.value(2).toString();
            controller.isActive     = singleData.value(3).toBool();

            result.append(controller);
        }

        return result;
    }
};

#endif // CONTROLLER_H
