#include "DeviceTypeDelegate.h"
#include <QComboBox>

DeviceTypeDelegate::DeviceTypeDelegate( QObject* parent)
    : QStyledItemDelegate(parent)
{
}

DeviceTypeDelegate::~DeviceTypeDelegate()
{

}

QWidget* DeviceTypeDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const {

   if (index.column() != 1)
       return QStyledItemDelegate::createEditor(parent, option, index);

   QComboBox* cb = new QComboBox(parent);

   cb->addItem("Расходомер", 0);
   cb->addItem("Клапан", 1);
   return cb;
}

void DeviceTypeDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const {

   if (QComboBox* cb = qobject_cast<QComboBox*>(editor)) {
      int deviceType = index.data(Qt::EditRole).toInt();
      int cbIndex = cb->findData(deviceType);
      if (cbIndex >= 0)
          cb->setCurrentIndex(cbIndex);
   }
   else
   {
       QStyledItemDelegate::setEditorData(editor, index);
   }
}

void DeviceTypeDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const {

   if (QComboBox* cb = qobject_cast<QComboBox*>(editor))

       model->setData(index, cb->currentData(), Qt::EditRole);
   else
       QStyledItemDelegate::setModelData(editor, model, index);
}

