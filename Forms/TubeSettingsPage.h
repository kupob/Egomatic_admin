#ifndef TUBESETTINGSPAGE_H
#define TUBESETTINGSPAGE_H

#include <QWidget>
#include <QPointer>
#include "ItemPage.h"
#include <Models/TubeSettingsPageModel.h>

class TubeSettingsPage : public ItemPage
{
public:
    TubeSettingsPage(QWidget *parent = 0);
    ~TubeSettingsPage();

protected slots:
    void save();
    void cancel();

private:
    QPointer<TubeSettingsPageModel> _model;
};

#endif // TUBESETTINGSPAGE_H
