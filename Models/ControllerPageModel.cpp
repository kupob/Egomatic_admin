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
    return _controllers.count();
}

int ControllerPageModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return Controller::columnCount;
}

QVariant ControllerPageModel::data(const QModelIndex &index, int role) const
{
    Controller controller = _controllers.value(index.row());
    if (role == Qt::DisplayRole)
    {
        if (controller.isValid())
        {
            return controller.data(index.column());
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

    Controller controller = _controllers.value(index.row());
    controller.setData(index.column(), value);
    _controllers[index.row()] = controller;

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

    _controllers.clear();
    _removedControllers.clear();

    ControllerGateway controllerGateway;
    controllerGateway.getControllers(_controllers);

    endResetModel();

}

void ControllerPageModel::addItem(const Controller &controller)
{
    beginInsertRows(QModelIndex(), _controllers.count(), _controllers.count());

    _controllers.append(controller);

    endInsertRows();
}

void ControllerPageModel::removeItem(const QModelIndex &index)
{
    beginRemoveRows(QModelIndex(), index.row(), index.row());

    Controller controller = _controllers.takeAt(index.row());
    controller.isActive = false;
    _removedControllers.append(controller);

    endRemoveRows();
}

QList<Controller> ControllerPageModel::getControllers()
{
    QList<Controller> result = _controllers;
    result += _removedControllers;
    return result;
}
