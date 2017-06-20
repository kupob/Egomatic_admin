#ifndef USERPAGE_H
#define USERPAGE_H

#include <QWidget>
#include <QPointer>
#include "ItemPage.h"
#include <Models/UserPageModel.h>

class UserPage : public ItemPage
{
public:
    UserPage(QWidget *parent = 0);
    ~UserPage();

protected slots:
    void addItem();
    void removeItem();

    void save();
    void cancel();

private:
    QPointer<UserPageModel> _model;
};

#endif // USERPAGE_H
