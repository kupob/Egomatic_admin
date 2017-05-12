#ifndef DEVICEPAGEMODEL_H
#define DEVICEPAGEMODEL_H

#include <QObject>
#include <QAbstractTableModel>
#include <ORM/Device.h>

class DevicePageModel : public QAbstractTableModel
{
public:
    DevicePageModel(QObject *parent = Q_NULLPTR);
    ~DevicePageModel();

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex &index) const;

    void resetData();
    void addItem(const Device& item);
    void removeItem(const QModelIndex& index);

    QList<Device> getDevices();

private:
    QList<Device> _items;
    QList<Device> _removedItems;
};

#endif // DEVICEPAGEMODEL_H
