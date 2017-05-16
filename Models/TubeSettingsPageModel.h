#ifndef TUBESETTINGSPAGEMODEL_H
#define TUBESETTINGSPAGEMODEL_H

#include <QObject>
#include <QAbstractTableModel>
#include <ORM/TubeSettings.h>

class Drink;

class TubeSettingsPageModel : public QAbstractTableModel
{
public:
    TubeSettingsPageModel(QObject *parent = Q_NULLPTR);
    ~TubeSettingsPageModel();

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex &index) const;

    void resetData();

    QList<TubeSettings> getItems();

private:
    QList<TubeSettings> _items;
    QHash<QString, Drink> _drinks;
};

#endif // TUBESETTINGSPAGEMODEL_H
