#ifndef CUSTOMERPAGE_H
#define CUSTOMERPAGE_H

#include <QWidget>
#include <QPointer>
#include "ItemPage.h"
#include <Models/CustomerPageModel.h>

class CustomerPage : public ItemPage
{
public:
    CustomerPage(QWidget *parent = 0);
    ~CustomerPage();

protected slots:
    void addItem();
    void removeItem();

    void save();
    void cancel();

private:
    QPointer<CustomerPageModel> _model;
};

#endif // CUSTOMERPAGE_H
