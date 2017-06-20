#ifndef USERPAGEMODEL_H
#define USERPAGEMODEL_H

#include <QObject>
#include <QAbstractTableModel>
#include <ORM/User.h>

class UserPageModel : public QAbstractTableModel
{
public:
    UserPageModel(QObject *parent = Q_NULLPTR);
    ~UserPageModel();

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex &index) const;

    void resetData();
    void addItem(const User& item);
    void removeItem(const QModelIndex& index);

    QList<User> getItems();

private:
    QList<User> _items;
    QList<User> _removedItems;
};

#endif // USERPAGEMODEL_H
