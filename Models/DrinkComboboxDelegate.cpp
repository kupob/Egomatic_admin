#include "DrinkComboboxDelegate.h"
#include <QComboBox>

#include <ORM/DrinkGateway.h>

DrinkComboboxDelegate::DrinkComboboxDelegate( QObject* parent)
    : QStyledItemDelegate(parent)
{
}

DrinkComboboxDelegate::~DrinkComboboxDelegate()
{

}

QWidget* DrinkComboboxDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const {

   if (index.column() != 1)
       return QStyledItemDelegate::createEditor(parent, option, index);

   QComboBox* cb = new QComboBox(parent);

   DrinkGateway gateway;
   QList<Drink> drinks;
   gateway.getItems(drinks);

   cb->addItem("---", QString(""));
   foreach (Drink drink, drinks)
   {
       cb->addItem(drink.name, drink.drinkId);
   }

   return cb;
}

void DrinkComboboxDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const {

   if (QComboBox* cb = qobject_cast<QComboBox*>(editor)) {
      QString uuid = index.data(Qt::EditRole).toString();
      int cbIndex = cb->findData(uuid);
      if (cbIndex >= 0)
          cb->setCurrentIndex(cbIndex);
   }
   else
   {
       QStyledItemDelegate::setEditorData(editor, index);
   }
}

void DrinkComboboxDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const {

   if (QComboBox* cb = qobject_cast<QComboBox*>(editor))

       model->setData(index, cb->currentData(), Qt::EditRole);
   else
       QStyledItemDelegate::setModelData(editor, model, index);
}

