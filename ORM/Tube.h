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

    QString tubeId;   // uuid NOT NULL, -- Идентификатор трубки
    int     number;   // integer, -- Номер трубки
    bool    isActive; // boolean DEFAULT true, -- Флаг активности

    static const int fieldCount = 3;
    static const int columnCount = 1;

public:
    QVariant data(int position) const
    {
        switch (position) {
        case 0:     return QVariant::fromValue(number);
        default:    return QVariant();
        }
    }

    void setData(int position, QVariant value)
    {
        switch (position) {
        case 0:
            number = value.toInt();
            break;
        default:
            break;
        }
    }

    static QVariant headerData(int position)
    {
        switch (position) {
        case 0:     return QString("Номер трубки");
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
            tube.tubeId   = singleData.value(0).toString();
            tube.number   = singleData.value(1).toInt();
            tube.isActive = singleData.value(2).toBool();

            result.append(tube);
        }

        return result;
    }
};

#endif // TUBE_H
