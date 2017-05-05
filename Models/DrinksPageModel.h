#ifndef DRINKSPAGEMODEL_H
#define DRINKSPAGEMODEL_H

#include <QObject>
#include <QAbstractTableModel>
#include <ORM/Drink.h>

class DrinksPageModel : public QAbstractTableModel
{
public:
    DrinksPageModel(QObject *parent = Q_NULLPTR);
    ~DrinksPageModel();

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    void resetData();
    void addItem(const Drink& drink);
    void removeItem(const QModelIndex& index);

private:
    QList<Drink> _drinks;
};

#endif // DRINKSPAGEMODEL_H
