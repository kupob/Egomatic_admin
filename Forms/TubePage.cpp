#include "TubePage.h"
#include "ui_ItemPage.h"
#include <Utils/DbAdapter.h>
#include <ORM/TubeGateway.h>

TubePage::TubePage(QWidget *parent) :
    ItemPage(parent)
{
    _model = QPointer<TubePageModel>(new TubePageModel(this));
    ui->tableView->setModel(_model.data());
}

TubePage::~TubePage()
{

}

void TubePage::addItem()
{
    Tube tube;
    tube.tubeId = DbAdapter::instance()->getUuid();
    _model->addItem(tube);
}

void TubePage::removeItem()
{
    QModelIndex current = ui->tableView->currentIndex();
    _model->removeItem(current);
}

void TubePage::save()
{
    QList<Tube> tubes = _model->getTubes();
    TubeGateway tubeGateway;

    bool ok = false;
    if (!tubes.isEmpty())
        ok = tubeGateway.saveTubes(tubes);

    if (ok)
        _model->resetData();
}

void TubePage::cancel()
{
    _model->resetData();
}
