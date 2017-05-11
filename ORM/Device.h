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

    QString deviceId;           //   deviceid uuid NOT NULL, -- Устройства контроля пролива напитка (счетчик/клапан)
    int     pinNumber;          //   pinnumber integer, -- Номер пина на контроллере
    int     deviceType;         //   devicetype integer, -- 0 - расходомер, 1 - клапан
    int     controllerNumber;   //   controllernumber integer, -- Номер контроллера, контролирующего устройство
    int     tubeNumber;         //   tubenumber integer, -- Номер трубки
    bool    isActive;           //   isactive boolean DEFAULT true, -- Флаг активности

    static const int fieldCount = 6;
    static const int columnCount = 4;

public:
    QVariant data(int position) const
    {
        switch (position) {
        case 0:     return QVariant::fromValue(deviceId);
        case 1:     return QVariant::fromValue(pinNumber);
        case 2:     return QVariant::fromValue(deviceType);
        case 3:     return QVariant::fromValue(controllerNumber);
        case 4:     return QVariant::fromValue(tubeNumber);
        default:    return QVariant();
        }
    }

    void setData(int position, QVariant value)
    {
        switch (position) {
        case 0:
            deviceId = value.toString();
            break;
        case 1:
            pinNumber    = value.toInt();
            break;
        case 2:
            deviceType   = value.toInt();
            break;
        case 3:
            controllerNumber = value.toInt();
            break;
        case 4:
            tubeNumber = value.toInt();
            break;
        default:
            break;
        }
    }

    static QVariant headerData(int position)
    {
        switch (position) {
        case 0:     return QString("Контроллер");
        case 1:     return QString("Номер пина на контроллере");
        case 2:     return QString("Тип устройства");
        case 3:     return QString("Номер контроллера");
        case 4:     return QString("Номер трубки");
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
            device.deviceId           = singleData.value(0).toString();
            device.pinNumber          = singleData.value(1).toInt();
            device.deviceType         = singleData.value(2).toInt();
            device.controllerNumber   = singleData.value(3).toInt();
            device.tubeNumber         = singleData.value(4).toInt();
            device.isActive           = singleData.value(5).toBool();

            result.append(device);
        }

        return result;
    }
};

#endif // DEVICE_H
