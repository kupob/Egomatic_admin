#include "UserPageModel.h"
#include <ORM/UserGateway.h>

UserPageModel::UserPageModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    resetData();
}

UserPageModel::~UserPageModel()
{

}

int UserPageModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return _items.count();
}

int UserPageModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return User::columnCount;
}

QVariant UserPageModel::data(const QModelIndex &index, int role) const
{
    User item = _items.value(index.row());
    if (role == Qt::DisplayRole)
    {
        if (item.isValid())
        {
            return item.data(index.column());
        }
    }

    return QVariant();
}

QVariant UserPageModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Vertical)
        return QVariant();

    if (role == Qt::DisplayRole)
    {
        return User::headerData(section);
    }

    return QVariant();
}

bool UserPageModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Q_UNUSED(role);

    User item = _items.value(index.row());
    item.setData(index.column(), value);
    _items[index.row()] = item;

    emit dataChanged(index, index);

    return true;
}

Qt::ItemFlags UserPageModel::flags(const QModelIndex &index) const
{
    Q_UNUSED(index);

    Qt::ItemFlags flags;
    flags |= Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
    return flags;
}

void UserPageModel::resetData()
{
    beginResetModel();

    _items.clear();
    _removedItems.clear();

    UserGateway itemGateway;
    itemGateway.getItems(_items);

    endResetModel();

}

void UserPageModel::addItem(const User &item)
{
    beginInsertRows(QModelIndex(), _items.count(), _items.count());

    _items.append(item);

    endInsertRows();
}

void UserPageModel::removeItem(const QModelIndex &index)
{
    beginRemoveRows(QModelIndex(), index.row(), index.row());

    User item = _items.takeAt(index.row());
    item.isActive = false;
    _removedItems.append(item);

    endRemoveRows();
}

QList<User> UserPageModel::getItems()
{
    QList<User> result = _items;
    result += _removedItems;
    return result;
}
