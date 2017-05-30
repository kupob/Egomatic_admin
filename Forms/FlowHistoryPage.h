#ifndef FLOWHISTORYPAGE_H
#define FLOWHISTORYPAGE_H

#include <QWidget>
#include <QPointer>
#include "ItemPage.h"
#include <Models/FlowHistoryPageModel.h>

class FlowHistoryPage : public ItemPage
{
public:
    FlowHistoryPage(QWidget *parent = 0);
    ~FlowHistoryPage();

private:
    QPointer<FlowHistoryPageModel> _model;
};

#endif // FLOWHISTORYPAGE_H
