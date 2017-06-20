#ifndef CUSTOMERPAGEMODEL_H
#define CUSTOMERPAGEMODEL_H

#include <QObject>
#include <QAbstractTableModel>
#include <ORM/Customer.h>

class CustomerPageModel : public QAbstractTableModel
{
public:
    CustomerPageModel(QObject *parent = Q_NULLPTR);
    ~CustomerPageModel();

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex &index) const;

    void resetData();
    void addItem(const Customer& item);
    void removeItem(const QModelIndex& index);

    QList<Customer> getItems();

private:
    QList<Customer> _items;
    QList<Customer> _removedItems;
};

#endif // CUSTOMERPAGEMODEL_H
