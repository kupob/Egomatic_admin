#ifndef FLOWHISTORYPAGEMODEL_H
#define FLOWHISTORYPAGEMODEL_H

#include <QObject>
#include <QAbstractTableModel>
#include <ORM/FlowHistory.h>

class Drink;
class Customer;

class FlowHistoryPageModel : public QAbstractTableModel
{
public:
    FlowHistoryPageModel(QObject *parent = Q_NULLPTR);
    ~FlowHistoryPageModel();

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    void resetData();

private:
    QList<FlowHistory> _items;
    QHash<QString, Drink> _drinks;
    QHash<QString, Customer> _customers;
};

#endif // FLOWHISTORYPAGEMODEL_H
