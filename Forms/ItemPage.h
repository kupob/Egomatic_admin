#ifndef ITEMPAGE_H
#define ITEMPAGE_H

#include <QWidget>

namespace Ui {
class ItemPage;
}

class ItemPage : public QWidget
{
    Q_OBJECT

public:
    explicit ItemPage(QWidget *parent = 0);
    ~ItemPage();

protected slots:
    virtual void addItem();
    virtual void removeItem();

    virtual void save();
    virtual void cancel();

protected:
    Ui::ItemPage *ui;
};

#endif // ITEMPAGE_H
