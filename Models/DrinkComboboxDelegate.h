#ifndef DRINKCOMBOBOXDELEGATE_H
#define DRINKCOMBOBOXDELEGATE_H

#include <QStyledItemDelegate>
#include <QComboBox>

class Drink;

class DrinkComboboxDelegate : public QStyledItemDelegate
{
public:
    DrinkComboboxDelegate(QObject* parent=0);
    ~DrinkComboboxDelegate();

    virtual QWidget* createEditor(QWidget* parent,
                                  const QStyleOptionViewItem& option,
                                  const QModelIndex& index) const;

    virtual void setEditorData(QWidget* editor,
                               const QModelIndex& index) const;

    virtual void setModelData(QWidget* editor,
                              QAbstractItemModel* model,
                              const QModelIndex& index) const;
};

#endif // DRINKCOMBOBOXDELEGATE_H
