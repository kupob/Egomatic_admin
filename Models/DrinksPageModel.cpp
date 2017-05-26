#include "DrinksPageModel.h"
#include <ORM/DrinkGateway.h>

DrinksPageModel::DrinksPageModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    resetData();
}

DrinksPageModel::~DrinksPageModel()
{

}

int DrinksPageModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return _items.count();
}

int DrinksPageModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return Drink::columnCount;
}

QVariant DrinksPageModel::data(const QModelIndex &index, int role) const
{
    Drink item = _items.value(index.row());
    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        if (item.isValid())
        {
            return item.data(index.column());
        }
    }

    return QVariant();
}

QVariant DrinksPageModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Vertical)
        return QVariant();

    if (role == Qt::DisplayRole)
    {
        return Drink::headerData(section);
    }

    return QVariant();
}

bool DrinksPageModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Q_UNUSED(role);

    Drink item = _items.value(index.row());
    item.setData(index.column(), value);
    _items[index.row()] = item;

    emit dataChanged(index, index);

    return true;
}

Qt::ItemFlags DrinksPageModel::flags(const QModelIndex &index) const
{
    Q_UNUSED(index);

    Qt::ItemFlags flags;
    flags |= Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
    return flags;
}

void DrinksPageModel::resetData()
{
    beginResetModel();

    _items.clear();
    _removedItems.clear();

    DrinkGateway itemGateway;
    itemGateway.getItems(_items);

    endResetModel();

}

void DrinksPageModel::addItem(const Drink &item)
{
    beginInsertRows(QModelIndex(), _items.count(), _items.count());

    _items.append(item);

    endInsertRows();
}

void DrinksPageModel::removeItem(const QModelIndex &index)
{
    beginRemoveRows(QModelIndex(), index.row(), index.row());

    Drink item = _items.takeAt(index.row());
    item.isActive = false;
    _removedItems.append(item);

    endRemoveRows();
}

QList<Drink> DrinksPageModel::getItems()
{
    QList<Drink> result = _items;
    result += _removedItems;
    return result;
}
