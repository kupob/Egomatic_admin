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
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex &index) const;

    void resetData();
    void addItem(const Drink& item);
    void removeItem(const QModelIndex& index);

    QList<Drink> getItems();

private:
    QList<Drink> _items;
    QList<Drink> _removedItems;
};

#endif // DRINKSPAGEMODEL_H
