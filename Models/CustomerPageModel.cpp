#include "CustomerPageModel.h"
#include <ORM/CustomerGateway.h>

CustomerPageModel::CustomerPageModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    resetData();
}

CustomerPageModel::~CustomerPageModel()
{

}

int CustomerPageModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return _items.count();
}

int CustomerPageModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return Customer::columnCount;
}

QVariant CustomerPageModel::data(const QModelIndex &index, int role) const
{
    Customer item = _items.value(index.row());
    if (role == Qt::DisplayRole)
    {
        if (item.isValid())
        {
            return item.data(index.column());
        }
    }

    return QVariant();
}

QVariant CustomerPageModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Vertical)
        return QVariant();

    if (role == Qt::DisplayRole)
    {
        return Customer::headerData(section);
    }

    return QVariant();
}

bool CustomerPageModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Q_UNUSED(role);

    Customer item = _items.value(index.row());
    item.setData(index.column(), value);
    _items[index.row()] = item;

    emit dataChanged(index, index);

    return true;
}

Qt::ItemFlags CustomerPageModel::flags(const QModelIndex &index) const
{
    Q_UNUSED(index);

    Qt::ItemFlags flags;

    flags |= Qt::ItemIsEnabled | Qt::ItemIsSelectable;

    if (index.column() != 2)
        flags |= Qt::ItemIsEditable;

    return flags;
}

void CustomerPageModel::resetData()
{
    beginResetModel();

    _items.clear();
    _removedItems.clear();

    CustomerGateway itemGateway;
    itemGateway.getItems(_items);

    endResetModel();

}

void CustomerPageModel::addItem(const Customer &item)
{
    beginInsertRows(QModelIndex(), _items.count(), _items.count());

    _items.append(item);

    endInsertRows();
}

void CustomerPageModel::removeItem(const QModelIndex &index)
{
    beginRemoveRows(QModelIndex(), index.row(), index.row());

    Customer item = _items.takeAt(index.row());
    item.isActive = false;
    _removedItems.append(item);

    endRemoveRows();
}

QList<Customer> CustomerPageModel::getItems()
{
    QList<Customer> result = _items;
    result += _removedItems;
    return result;
}
