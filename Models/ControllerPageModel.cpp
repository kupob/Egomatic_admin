#include "ControllerPageModel.h"
#include <ORM/ControllerGateway.h>

ControllerPageModel::ControllerPageModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    resetData();
}

ControllerPageModel::~ControllerPageModel()
{

}

int ControllerPageModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return _items.count();
}

int ControllerPageModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return Controller::columnCount;
}

QVariant ControllerPageModel::data(const QModelIndex &index, int role) const
{
    Controller item = _items.value(index.row());
    if (role == Qt::DisplayRole)
    {
        if (item.isValid())
        {
            return item.data(index.column());
        }
    }

    return QVariant();
}

QVariant ControllerPageModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Vertical)
        return QVariant();

    if (role == Qt::DisplayRole)
    {
        return Controller::headerData(section);
    }

    return QVariant();
}

bool ControllerPageModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Q_UNUSED(role);

    Controller item = _items.value(index.row());
    item.setData(index.column(), value);
    _items[index.row()] = item;

    emit dataChanged(index, index);

    return true;
}

Qt::ItemFlags ControllerPageModel::flags(const QModelIndex &index) const
{
    Q_UNUSED(index);

    Qt::ItemFlags flags;
    flags |= Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
    return flags;
}

void ControllerPageModel::resetData()
{
    beginResetModel();

    _items.clear();
    _removedItems.clear();

    ControllerGateway itemGateway;
    itemGateway.getControllers(_items);

    endResetModel();

}

void ControllerPageModel::addItem(const Controller &item)
{
    beginInsertRows(QModelIndex(), _items.count(), _items.count());

    _items.append(item);

    endInsertRows();
}

void ControllerPageModel::removeItem(const QModelIndex &index)
{
    beginRemoveRows(QModelIndex(), index.row(), index.row());

    Controller item = _items.takeAt(index.row());
    item.isActive = false;
    _removedItems.append(item);

    endRemoveRows();
}

QList<Controller> ControllerPageModel::getControllers()
{
    QList<Controller> result = _items;
    result += _removedItems;
    return result;
}
