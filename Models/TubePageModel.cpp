#include "TubePageModel.h"
#include <ORM/TubeGateway.h>

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
    return _tubes.count();
}

int TubePageModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return Tube::columnCount;
}

QVariant TubePageModel::data(const QModelIndex &index, int role) const
{
    Tube tube = _tubes.value(index.row());
    if (role == Qt::DisplayRole)
    {
        if (tube.isValid())
        {
            return tube.data(index.column());
        }
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

    Tube tube = _tubes.value(index.row());
    tube.setData(index.column(), value);
    _tubes[index.row()] = tube;

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

    _tubes.clear();
    _removedTubes.clear();

    TubeGateway tubeGateway;
    tubeGateway.getTubes(_tubes);

    endResetModel();

}

void TubePageModel::addItem(const Tube &tube)
{
    beginInsertRows(QModelIndex(), _tubes.count(), _tubes.count());

    _tubes.append(tube);
    _tubes.last().number = _tubes.count();

    endInsertRows();
}

void TubePageModel::removeItem(const QModelIndex &index)
{
    beginRemoveRows(QModelIndex(), index.row(), index.row());

    Tube tube = _tubes.takeAt(index.row());
    tube.isActive = false;
    _removedTubes.append(tube);

    endRemoveRows();
}

QList<Tube> TubePageModel::getTubes()
{
    QList<Tube> result = _tubes;
    result += _removedTubes;
    return result;
}
