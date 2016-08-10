#include "fcombine.h"

/*****************************************************************************
 *
 *****************************************************************************/
FCombine::FCombine(QObject* parent) : Filter(parent)
{
}

FCombine::~FCombine()
{

}

/*****************************************************************************
 *
 *****************************************************************************/
QString FCombine::getName()
{
    return QString("Combine");
}

/*****************************************************************************
 *
 *****************************************************************************/
QString FCombine::getCaption()
{
    return QString("Combine");
}

/*****************************************************************************
 *
 *****************************************************************************/
QVector<DatInfo> FCombine::getInputTypes()
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
QVector<DatInfo> FCombine::getOutputTypes()
{
    QVector<DatInfo> ans;
    ans.push_back(DatInfo(IMAGE3, "Color Image"));
    return ans;
}

/*****************************************************************************
 *
 *****************************************************************************/
void FCombine::showConfig()
{
    dialog.exec();
}

/*****************************************************************************
 *
 *****************************************************************************/
QMap<QString, QVariant> FCombine::getData()
{
    QMap<QString, QVariant> ans;
    ans.insert("Name", QVariant(getName()));

    return ans;
}

void FCombine::setData(QMap<QString, QVariant> data)
{

}

/*****************************************************************************
 *
 *****************************************************************************/
void FCombine::reset()
{

}

/*****************************************************************************
 *
 *****************************************************************************/
QVector<Data*> FCombine::run(QVector<Data*> dat)
{

    DImage1* r = dynamic_cast<DImage1*>(dat[0]);
    DImage1* g = dynamic_cast<DImage1*>(dat[1]);
    DImage1* b = dynamic_cast<DImage1*>(dat[2]);

    vector<Mat> c;

    c.push_back(b->getImage());
    c.push_back(g->getImage());
    c.push_back(r->getImage());

    Mat a;
    merge(c, a);

    DImage3* merged = new DImage3();
    merged->setImage(a);

    QVector<Data*> ans;
    ans.push_back(merged);

    return ans;

}

static FilterFactory<FCombine> fCombine;
