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
    return _drinks.count();
}

int DrinksPageModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return Drink::columnCount;
}

QVariant DrinksPageModel::data(const QModelIndex &index, int role) const
{
    Drink drink = _drinks.value(index.row());
    if (role == Qt::DisplayRole)
    {
        if (drink.isValid())
        {
            return drink.data(index.column());
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

    Drink drink = _drinks.value(index.row());
    drink.setData(index.column(), value);
    _drinks[index.row()] = drink;

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

    _drinks.clear();
    _removedDrinks.clear();

    DrinkGateway drinkGateway;
    drinkGateway.getDrinks(_drinks);

    endResetModel();

}

void DrinksPageModel::addItem(const Drink &drink)
{
    beginInsertRows(QModelIndex(), _drinks.count(), _drinks.count());

    _drinks.append(drink);

    endInsertRows();
}

void DrinksPageModel::removeItem(const QModelIndex &index)
{
    beginRemoveRows(QModelIndex(), index.row(), index.row());

    Drink drink = _drinks.takeAt(index.row());
    drink.isActive = false;
    _removedDrinks.append(drink);

    endRemoveRows();
}

QList<Drink> DrinksPageModel::getDrinks()
{
    QList<Drink> result = _drinks;
    result += _removedDrinks;
    return result;
}
