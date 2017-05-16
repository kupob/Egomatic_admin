#include "TubeSettingsPageModel.h"
#include <ORM/TubeSettingsGateway.h>
#include <ORM/DrinkGateway.h>

TubeSettingsPageModel::TubeSettingsPageModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    resetData();
}

TubeSettingsPageModel::~TubeSettingsPageModel()
{

}

int TubeSettingsPageModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return _items.count();
}

int TubeSettingsPageModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return TubeSettings::columnCount;
}

QVariant TubeSettingsPageModel::data(const QModelIndex &index, int role) const
{
    TubeSettings item = _items.value(index.row());
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
        if (index.column() == 0)
            return item.drinkId;
    }

    return QVariant();
}

QVariant TubeSettingsPageModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Vertical)
        return QVariant();

    if (role == Qt::DisplayRole)
    {
        return TubeSettings::headerData(section);
    }

    return QVariant();
}

bool TubeSettingsPageModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Q_UNUSED(role);
    QString data = value.toString();

    TubeSettings item = _items.value(index.row());
    item.setData(index.column(), value);
    _items[index.row()] = item;

    emit dataChanged(index, index);

    return true;
}

Qt::ItemFlags TubeSettingsPageModel::flags(const QModelIndex &index) const
{
    Q_UNUSED(index);

    Qt::ItemFlags flags;
    flags |= Qt::ItemIsEnabled | Qt::ItemIsSelectable;

    if (index.column() != 0)
        flags |= Qt::ItemIsEditable;

    return flags;
}

void TubeSettingsPageModel::resetData()
{
    beginResetModel();

    _items.clear();
    _drinks.clear();

    TubeSettingsGateway itemGateway;
    itemGateway.getItems(_items);

    QList<Drink> drinks;
    DrinkGateway drinkGateway;
    drinkGateway.getItems(drinks);
    foreach (Drink drink, drinks)
        _drinks.insert(drink.drinkId, drink);

    endResetModel();

}

QList<TubeSettings> TubeSettingsPageModel::getItems()
{
    return _items;
}
