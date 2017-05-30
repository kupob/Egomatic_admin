#include "TubePageModel.h"
#include <ORM/TubeGateway.h>
#include <ORM/DrinkGateway.h>

TubePageModel::TubePageModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    resetData();
}

TubePageModel::~TubePageModel()
{

}

int TubePageModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return _items.count();
}

int TubePageModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return Tube::columnCount;
}

QVariant TubePageModel::data(const QModelIndex &index, int role) const
{
    Tube item = _items.value(index.row());
    if (role == Qt::DisplayRole)
    {
        if (index.column() == 1)
        {
            Drink drink = _drinks.value(item.drinkId);
            if (drink.isValid())
                return drink.name;
            else
                return QString("---");
        }
        return item.data(index.column());
    }
    else if (role == Qt::EditRole)
    {
        if (index.column() == 1)
            return item.drinkId;
    }

    return QVariant();
}

QVariant TubePageModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Vertical)
        return QVariant();

    if (role == Qt::DisplayRole)
    {
        return Tube::headerData(section);
    }

    return QVariant();
}

bool TubePageModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Q_UNUSED(role);

    Tube item = _items.value(index.row());
    item.setData(index.column(), value);
    _items[index.row()] = item;

    emit dataChanged(index, index);

    return true;
}

Qt::ItemFlags TubePageModel::flags(const QModelIndex &index) const
{
    Q_UNUSED(index);

    Qt::ItemFlags flags;
    flags |= Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
    return flags;
}

void TubePageModel::resetData()
{
    beginResetModel();

    _items.clear();
    _removedItems.clear();

    TubeGateway itemGateway;
    itemGateway.getItems(_items);

    QList<Drink> drinks;
    DrinkGateway drinkGateway;
    drinkGateway.getItems(drinks);
    foreach (Drink drink, drinks)
        _drinks.insert(drink.drinkId, drink);

    endResetModel();

}

void TubePageModel::addItem(const Tube &item)
{
    beginInsertRows(QModelIndex(), _items.count(), _items.count());

    _items.append(item);
    _items.last().number = _items.count();

    endInsertRows();
}

void TubePageModel::removeItem(const QModelIndex &index)
{
    beginRemoveRows(QModelIndex(), index.row(), index.row());

    Tube item = _items.takeAt(index.row());
    item.isActive = false;
    _removedItems.append(item);

    endRemoveRows();
}

QList<Tube> TubePageModel::getItems()
{
    QList<Tube> result = _items;
    result += _removedItems;
    return result;
}
