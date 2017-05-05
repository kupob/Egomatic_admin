#include "DrinksPageModel.h"
#include <Utils/DbAdapter.h>

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
    return _drinks.count();
}

int DrinksPageModel::columnCount(const QModelIndex &parent) const
{
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

void DrinksPageModel::resetData()
{
    DbAdapter *db = DbAdapter::instance();

    QList< QList< QVariant > > data;
    bool ok = db->getDrinks(data);
    if (ok)
    {
        _drinks = Drink::convertFromData(data);
    }
}

void DrinksPageModel::addItem(const Drink &drink)
{
    beginInsertRows(QModelIndex(), _drinks.count(), _drinks.count());

    _drinks.append(drink);

    endInsertRows();
}

void DrinksPageModel::removeItem(const QModelIndex &index)
{
    beginRemoveRows(QModelIndex(), _drinks.count(), _drinks.count());

    _drinks.removeAt(index.row());

    endRemoveRows();
}
