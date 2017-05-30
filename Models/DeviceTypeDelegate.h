#ifndef DEVICETYPEDELEGATE_H
#define DEVICETYPEDELEGATE_H

#include <QStyledItemDelegate>
#include <QComboBox>

class DeviceTypeDelegate : public QStyledItemDelegate
{
public:
    DeviceTypeDelegate(QObject* parent=0);
    ~DeviceTypeDelegate();

    virtual QWidget* createEditor(QWidget* parent,
                                  const QStyleOptionViewItem& option,
                                  const QModelIndex& index) const;

    virtual void setEditorData(QWidget* editor,
                               const QModelIndex& index) const;

    virtual void setModelData(QWidget* editor,
                              QAbstractItemModel* model,
                              const QModelIndex& index) const;
};

#endif // DEVICETYPEDELEGATE_H
