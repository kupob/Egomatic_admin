#ifndef TUBE_H
#define TUBE_H

#include <QString>
#include <QList>
#include <QVariant>

class Tube
{
public:
    Tube()
    {
        number = 0;
        isActive = true;
    }

    bool isValid() { return !tubeId.isEmpty(); }

    QString tubeId;             // uuid NOT NULL, -- Идентификатор трубки
    int     number;             // integer, -- Номер трубки
    QString tubeSettingsId;     // uuid NOT NULL, -- Идентификатор связи (lnk_tubesettings)
    QString drinkId;            // uuid, -- Идентификатор напитка (lnk_tubesettings)
    bool    isUnderMaintenance; // boolean DEFAULT false, -- Флаг режима обслуживания (lnk_tubesettings)
    bool    isActive;           // boolean DEFAULT true, -- Флаг активности

    static const int fieldCount = 6;
    static const int columnCount = 3;

public:
    QVariant data(int position) const
    {
        switch (position) {
        case 0:     return QVariant::fromValue(number);
        case 1:     return QVariant::fromValue(drinkId);
        case 2:
        {
            return isUnderMaintenance ? QObject::tr("Да") : QObject::tr("Нет");
        }
        default:    return QVariant();
        }
    }

    void setData(int position, QVariant value)
    {
        switch (position) {
        case 0:
            number = value.toInt();
            break;
        case 1:
            drinkId = value.toString();
            break;
        case 2:
            isUnderMaintenance = value.toBool();
            break;
        default:
            break;
        }
    }

    static QVariant headerData(int position)
    {
        switch (position) {
        case 0:     return QString("Номер трубки");
        case 1:     return QString("Напиток");
        case 2:     return QString("Режим обслуживания");
        default:    return QVariant();
        }
    }

    static QList<Tube> convertFromData(QList< QList<QVariant> > data)
    {
        QList<Tube> result;

        foreach (auto singleData, data)
        {
            Q_ASSERT(singleData.size() == fieldCount);

            Tube tube;
            tube.tubeId             = singleData.value(0).toString();
            tube.number             = singleData.value(1).toInt();
            tube.tubeSettingsId     = singleData.value(2).toString();
            tube.drinkId            = singleData.value(3).toString();

            if (singleData.value(4).isValid())
                tube.isUnderMaintenance = singleData.value(4).toBool();
            else
                tube.isUnderMaintenance = false;

            tube.isActive = singleData.value(5).toBool();

            result.append(tube);
        }

        return result;
    }
};

#endif // TUBE_H
