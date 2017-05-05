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
    }

    bool isValid() { return !drinkId.isEmpty(); }

    QString drinkId;      // drinkid uuid NOT NULL, -- Идентификатор напитка
    QString name;         // name character varying(256), -- Наименование напитка
    float   cost;         // cost real DEFAULT 0.0, -- Стоимость напитка за 0.5л
    float   abv;          // abv real DEFAULT 0.0, -- Крепость напитка
    float   ibu;          // ibu real DEFAULT 0.0, -- Индекс горечи
    QString description;  // description text, -- Описание напитка

    static const int columnCount = 5;

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

    static QVariant headerData(int position)
    {
        switch (position) {
        case 0:     return QString("Идентификатор напитка");
        case 1:     return QString("Стоимость напитка за 0.5л");
        case 2:     return QString("Крепость напитка");
        case 3:     return QString("Индекс горечи");
        case 4:     return QString("Описание напитка");
        default:    return QVariant();
        }
    }

    static QList<Drink> convertFromData(QList< QList<QVariant> > data)
    {
        QList<Drink> result;

        foreach (auto singleData, data)
        {
            Q_ASSERT(singleData.size() == columnCount + 1);

            Drink drink;
            drink.drinkId     = singleData.value(0).toString();
            drink.name        = singleData.value(1).toString();
            drink.cost        = singleData.value(2).toFloat();
            drink.abv         = singleData.value(3).toFloat();
            drink.ibu         = singleData.value(4).toFloat();
            drink.description = singleData.value(5).toString();

            result.append(drink);
        }

        return result;
    }
};


#endif // DRINK_H
