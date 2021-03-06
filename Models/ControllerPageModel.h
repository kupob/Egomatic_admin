#ifndef CONTROLLERPAGEMODEL_H
#define CONTROLLERPAGEMODEL_H

#include <QObject>
#include <QAbstractTableModel>
#include <ORM/Controller.h>

class ControllerPageModel : public QAbstractTableModel
{
public:
    ControllerPageModel(QObject *parent = Q_NULLPTR);
    ~ControllerPageModel();

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex &index) const;

    void resetData();
    void addItem(const Controller& item);
    void removeItem(const QModelIndex& index);

    QList<Controller> getItems();

private:
    QList<Controller> _items;
    QList<Controller> _removedItems;
};

#endif // CONTROLLERPAGEMODEL_H
