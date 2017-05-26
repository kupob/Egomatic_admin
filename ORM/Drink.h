#ifndef DRINK_H
#define DRINK_H

#include <QString>
#include <QList>
#include <QVariant>

class Drink
{
public:
    Drink()
    {
        cost = 0.f;
        abv = 0.f;
        ibu = 0.f;
        isActive = true;
    }

    bool isValid() { return !drinkId.isEmpty(); }

    QString drinkId;      // drinkid uuid NOT NULL, -- Идентификатор напитка
    QString name;         // name character varying(256), -- Наименование напитка
    float   cost;         // cost real DEFAULT 0.0, -- Стоимость напитка
    float   costVolume;   // cost real DEFAULT 0.0, -- Объем напитка, для которого указана стоимость
    float   abv;          // abv real DEFAULT 0.0, -- Крепость напитка
    float   ibu;          // ibu real DEFAULT 0.0, -- Индекс горечи
    QString description;  // description text, -- Описание напитка
    bool    isActive;     // boolean DEFAULT true, -- Флаг активности

    static const int fieldCount = 8;
    static const int columnCount = 6;

public:
    QVariant data(int position) const
    {
        switch (position) {
        case 0:     return QVariant::fromValue(name);
        case 1:     return QVariant::fromValue(cost);
        case 2:     return QVariant::fromValue(costVolume);
        case 3:     return QVariant::fromValue(abv);
        case 4:     return QVariant::fromValue(ibu);
        case 5:     return QVariant::fromValue(description);
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
            costVolume  = value.toFloat();
            break;
        case 3:
            abv         = value.toFloat();
            break;
        case 4:
            ibu         = value.toFloat();
            break;
        case 5:
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
        case 1:     return QString("Цена напитка");
        case 2:     return QString("Объем напитка за указанную цену");
        case 3:     return QString("Крепость напитка");
        case 4:     return QString("Индекс горечи");
        case 5:     return QString("Описание напитка");
        default:    return QVariant();
        }
    }

    static QList<Drink> convertFromData(QList< QList<QVariant> > data)
    {
        QList<Drink> result;

        foreach (auto singleData, data)
        {
            Q_ASSERT(singleData.size() == fieldCount);

            Drink drink;
            drink.drinkId     = singleData.value(0).toString();
            drink.name        = singleData.value(1).toString();
            drink.cost        = singleData.value(2).toFloat();
            drink.costVolume  = singleData.value(3).toFloat();
            drink.abv         = singleData.value(4).toFloat();
            drink.ibu         = singleData.value(5).toFloat();
            drink.description = singleData.value(6).toString();
            drink.isActive    = singleData.value(7).toBool();

            result.append(drink);
        }

        return result;
    }
};


#endif // DRINK_H
