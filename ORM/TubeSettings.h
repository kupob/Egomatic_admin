#ifndef TUBESETTINGS_H
#define TUBESETTINGS_H

#include <QString>
#include <QList>
#include <QVariant>

class TubeSettings
{
public:
    TubeSettings()
    {
        number = 0;
        isActive = true;
    }

    bool isValid() const { return !tubeSettingsId.isEmpty(); }

    QString tubeSettingsId;     // uuid NOT NULL, -- Идентификатор трубки
    QString tubeId;             // uuid, -- Идентификатор трубки
    QString drinkId;            // uuid, -- Идентификатор напитка
    int     number;             // integer, -- Номер трубки
    bool    isUnderMaintenance; // режим обслуживания
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

    static QList<TubeSettings> convertFromData(QList< QList<QVariant> > data)
    {
        QList<TubeSettings> result;

        foreach (auto singleData, data)
        {
            Q_ASSERT(singleData.size() == fieldCount);

            TubeSettings tube;
            tube.tubeSettingsId     = singleData.value(0).toString();
            tube.tubeId             = singleData.value(1).toString();
            tube.drinkId            = singleData.value(2).toString();
            tube.number             = singleData.value(3).toInt();

            if (singleData.value(4).isValid())
                tube.isUnderMaintenance = singleData.value(4).toBool();
            else
                tube.isUnderMaintenance = false;

            if (singleData.value(5).isValid())
                tube.isActive           = singleData.value(5).toBool();
            else
                tube.isActive = true;

            result.append(tube);
        }

        return result;
    }
};

#endif // TUBESETTINGS_H
