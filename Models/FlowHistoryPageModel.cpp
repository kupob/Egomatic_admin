#include "FlowHistoryPageModel.h"
#include <ORM/FlowHistoryGateway.h>
#include <ORM/DrinkGateway.h>
#include <ORM/CustomerGateway.h>

FlowHistoryPageModel::FlowHistoryPageModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    resetData();
}

FlowHistoryPageModel::~FlowHistoryPageModel()
{

}

int FlowHistoryPageModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return _items.count();
}

int FlowHistoryPageModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return FlowHistory::columnCount;
}

QVariant FlowHistoryPageModel::data(const QModelIndex &index, int role) const
{
    FlowHistory item = _items.value(index.row());
    if (role == Qt::DisplayRole)
    {
        if (index.column() == 1)
        {
            Customer customer = _customers.value(item.customerId);
            if (customer.isValid())
                return customer.name;
            else
                return QString("---");
        }
        else if (index.column() == 2)
        {
            Drink drink = _drinks.value(item.drinkId);
            if (drink.isValid())
                return drink.name;
            else
                return QString("---");
        }
        return item.data(index.column());
    }

    return QVariant();
}

QVariant FlowHistoryPageModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Vertical)
        return QVariant();

    if (role == Qt::DisplayRole)
    {
        return FlowHistory::headerData(section);
    }

    return QVariant();
}

void FlowHistoryPageModel::resetData()
{
    beginResetModel();

    _items.clear();
    _drinks.clear();
    _customers.clear();

    FlowHistoryGateway itemGateway;
    itemGateway.getItems(_items);

    QList<Drink> drinks;
    DrinkGateway drinkGateway;
    drinkGateway.getItems(drinks);
    foreach (Drink drink, drinks)
        _drinks.insert(drink.drinkId, drink);

    QList<Customer> customers;
    CustomerGateway customerGateway;
    customerGateway.getItems(customers);
    foreach (Customer customer, customers)
        _customers.insert(customer.customerId, customer);

    endResetModel();

}
