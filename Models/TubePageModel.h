#ifndef TUBEPAGEMODEL_H
#define TUBEPAGEMODEL_H

#include <QObject>
#include <QAbstractTableModel>
#include <ORM/Tube.h>

class Drink;

class TubePageModel : public QAbstractTableModel
{
public:
    TubePageModel(QObject *parent = Q_NULLPTR);
    ~TubePageModel();

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex &index) const;

    void resetData();
    void addItem(const Tube& item);
    void removeItem(const QModelIndex& index);

    QList<Tube> getItems();

private:
    QList<Tube> _items;
    QList<Tube> _removedItems;
    QHash<QString, Drink> _drinks;
};

#endif // TUBEPAGEMODEL_H
