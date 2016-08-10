#include "fsplit.h"

/*****************************************************************************
 *
 *****************************************************************************/
FSplit::FSplit(QObject* parent) : Filter(parent)
{
}

/*****************************************************************************
 *
 *****************************************************************************/
FSplit::~FSplit()
{

}

/*****************************************************************************
 * Official name of the filter and what appears on the list on the left
 *****************************************************************************/
QString FSplit::getName()
{
    return QString("Split");
}

/*****************************************************************************
 * Caption that goes above the filter on the canvas.
 *****************************************************************************/
QString FSplit::getCaption()
{
    return QString("Split");
}

/*****************************************************************************
 *
 *****************************************************************************/
QVector<DatInfo> FSplit::getInputTypes()
{
    QVector<DatInfo> ans;
    ans.push_back(DatInfo(IMAGE3, "Color Image"));
    return ans;
}

/*****************************************************************************
 *
 *****************************************************************************/
QVector<DatInfo> FSplit::getOutputTypes()
{
    QVector<DatInfo> ans;

    ans.push_back(DatInfo(IMAGE1, "Red"));
    ans.push_back(DatInfo(IMAGE1, "Green"));
    ans.push_back(DatInfo(IMAGE1, "Blue"));

    return ans;
}

/*****************************************************************************
 *
 *****************************************************************************/
void FSplit::showConfig()
{
    dialog.exec();
}

/*****************************************************************************
 *
 *****************************************************************************/
QMap<QString, QVariant> FSplit::getData()
{
    QMap<QString, QVariant> ans;
    ans.insert("Name", QVariant(getName()));

    return ans;
}

/*****************************************************************************
 *
 *****************************************************************************/
void FSplit::setData(QMap<QString, QVariant> data)
{

}

/*****************************************************************************
 *
 *****************************************************************************/
void FSplit::reset()
{

}

/*****************************************************************************
 *
 *****************************************************************************/
QVector<Data*> FSplit::run(QVector<Data*> dat)
{
    DImage3* d = dynamic_cast<DImage3*>(dat[0]);

    vector<Mat> spl;

    split(d->getImage(), spl);

    DImage1* r = new DImage1();
    r->setImage(spl[2]);
    DImage1* g = new DImage1();
    g->setImage(spl[1]);
    DImage1* b = new DImage1();
    b->setImage(spl[0]);

    QVector<Data*> ans;
    ans.push_back(r);
    ans.push_back(g);
    ans.push_back(b);
    return ans;
}

static FilterFactory<FSplit> fSplit;
