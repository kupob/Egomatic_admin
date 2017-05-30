#include "DevicePageModel.h"
#include <ORM/DeviceGateway.h>

DevicePageModel::DevicePageModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    resetData();
}

DevicePageModel::~DevicePageModel()
{

}

int DevicePageModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return _items.count();
}

int DevicePageModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return Device::columnCount;
}

QVariant DevicePageModel::data(const QModelIndex &index, int role) const
{
    Device item = _items.value(index.row());
    if (role == Qt::DisplayRole)
    {
        if (item.isValid())
        {
            if (index.column() == 1)
            {
                int deviceType = item.data(1).toInt();
                if (deviceType == 0)
                    return "Расходомер";
                else if (deviceType == 1)
                    return "Клапан";
            }
            else
                return item.data(index.column());
        }
    }
    else if (role == Qt::EditRole && index.column() == 1)
        return item.data(1);

    return QVariant();
}

QVariant DevicePageModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Vertical)
        return QVariant();

    if (role == Qt::DisplayRole)
    {
        return Device::headerData(section);
    }

    return QVariant();
}

bool DevicePageModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Q_UNUSED(role);

    Device item = _items.value(index.row());
    item.setData(index.column(), value);
    _items[index.row()] = item;

    emit dataChanged(index, index);

    return true;
}

Qt::ItemFlags DevicePageModel::flags(const QModelIndex &index) const
{
    Q_UNUSED(index);

    Qt::ItemFlags flags;
    flags |= Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
    return flags;
}

void DevicePageModel::resetData()
{
    beginResetModel();

    _items.clear();
    _removedItems.clear();

    DeviceGateway itemGateway;
    itemGateway.getDevices(_items);

    endResetModel();

}

void DevicePageModel::addItem(const Device &item)
{
    beginInsertRows(QModelIndex(), _items.count(), _items.count());

    _items.append(item);

    endInsertRows();
}

void DevicePageModel::removeItem(const QModelIndex &index)
{
    beginRemoveRows(QModelIndex(), index.row(), index.row());

    Device item = _items.takeAt(index.row());
    item.isActive = false;
    _removedItems.append(item);

    endRemoveRows();
}

QList<Device> DevicePageModel::getDevices()
{
    QList<Device> result = _items;
    result += _removedItems;
    return result;
}
