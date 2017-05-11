#ifndef TUBEPAGE_H
#define TUBEPAGE_H

#include <QWidget>
#include <QPointer>
#include "ItemPage.h"
#include <Models/TubePageModel.h>

class TubePage : public ItemPage
{
public:
    TubePage(QWidget *parent = 0);
    ~TubePage();

protected slots:
    void addItem();
    void removeItem();

    void save();
    void cancel();

private:
    QPointer<TubePageModel> _model;
};

#endif // TUBEPAGE_H
