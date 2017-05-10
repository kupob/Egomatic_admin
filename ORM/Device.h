#ifndef DEVICE_H
#define DEVICE_H

#include <QString>
#include <QList>
#include <QVariant>

class Device
{
public:
    Device()
    {
        pinNumber = 0;
        deviceType = -1;
        isActive = true;
    }

    bool isValid() { return !deviceId.isEmpty(); }

    QString deviceId;       // deviceid uuid NOT NULL, -- Устройства контроля пролива напитка (счетчик/клапан)
    QString controllerId;   // controllerid uuid NOT NULL, -- Идентификатор контроллера, контролирующего устройство
    int     pinNumber;      // pinnumber integer, -- Номер пина на контроллере
    int     deviceType;     // devicetype integer, -- 0 - расходомер, 1 - клапан
    QString tubeId;         // tubeid uuid, -- Идентификатор трубки
    bool    isActive;       // isactive boolean DEFAULT true, -- Флаг активности

    static const int fieldCount = 6;
    static const int columnCount = 4;

    /*

public:
    QVariant data(int position) const
    {
        switch (position) {
        case 0:     return QVariant::fromValue(name);
        case 1:     return QVariant::fromValue(cost);
        case 2:     return QVariant::fromValue(abv);
        case 3:     return QVariant::fromValue(ibu);
        case 4:     return QVariant::fromValue(description);
        default:    return QVariant();
        }
    }

    void setData(int position, QVariant value)
    {
        switch (position) {
        case 0:
            name        = value.toString();
            break;
        case 1:
            cost        = value.toFloat();
            break;
        case 2:
            abv         = value.toFloat();
            break;
        case 3:
            ibu         = value.toFloat();
            break;
        case 4:
            description = value.toString();
            break;
        default:
            break;
        }
    }

    static QVariant headerData(int position)
    {
        switch (position) {
        case 0:     return QString("Наименование напитка");
        case 1:     return QString("Стоимость напитка за 0.5л");
        case 2:     return QString("Крепость напитка");
        case 3:     return QString("Индекс горечи");
        case 4:     return QString("Описание напитка");
        default:    return QVariant();
        }
    }

    static QList<Device> convertFromData(QList< QList<QVariant> > data)
    {
        QList<Device> result;

        foreach (auto singleData, data)
        {
            Q_ASSERT(singleData.size() == fieldCount);

            Device device;
            device.deviceId     = singleData.value(0).toString();
            device.name        = singleData.value(1).toString();
            device.cost        = singleData.value(2).toFloat();
            device.abv         = singleData.value(3).toFloat();
            device.ibu         = singleData.value(4).toFloat();
            device.description = singleData.value(5).toString();
            device.isActive    = singleData.value(6).toBool();

            result.append(device);
        }

        return result;
    }
    */
};

#endif // DEVICE_H
