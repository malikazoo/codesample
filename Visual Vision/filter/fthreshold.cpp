#include "fthreshold.h"

/*****************************************************************************
 *
 *****************************************************************************/
FThreshold::FThreshold(QObject *parent) :
    Filter(parent)
{
}

/*****************************************************************************
 *
 *****************************************************************************/
FThreshold::~FThreshold()
{

}

/*****************************************************************************
 *
 *****************************************************************************/
QString FThreshold::getName()
{
    return QString("Threshold");
}

/*****************************************************************************
 *
 *****************************************************************************/
QString FThreshold::getCaption()
{
    return QString("Threshold");
}

/*****************************************************************************
 *
 *****************************************************************************/
QVector<DatInfo> FThreshold::getInputTypes()
{
    QVector<DatInfo> ans;
    ans.push_back(DatInfo(IMAGE1,"Image"));
    return ans;
}

/*****************************************************************************
 *
 *****************************************************************************/
QVector<DatInfo> FThreshold::getOutputTypes()
{
    QVector<DatInfo> ans;
    ans.push_back(DatInfo(IMAGE1,"Image"));
    return ans;
}

/*****************************************************************************
 *
 *****************************************************************************/
void FThreshold::showConfig()
{
    dialog.exec();
}

/*****************************************************************************
 *
 *****************************************************************************/
QMap<QString, QVariant> FThreshold::getData()
{
    QMap<QString, QVariant> ans;
    ans.insert("Name", QVariant(getName()));

    ans.insert("Type", QVariant(dialog.getType()));
    ans.insert("Value", QVariant(dialog.getValue()));

    return ans;
}

/*****************************************************************************
 *
 *****************************************************************************/
void FThreshold::setData(QMap<QString, QVariant> data)
{
    if (data.contains("Type"))
    {
        dialog.setType(data["Type"].toInt());
    }

    if (data.contains("Value"))
    {
        dialog.setValue(data["Value"].toInt());
    }

}

/*****************************************************************************
 *
 *****************************************************************************/
void FThreshold::reset()
{

}

/*****************************************************************************
 *
 *****************************************************************************/
QVector<Data*> FThreshold::run(QVector<Data*> dat)
{
    QVector<Data*> ans;

    DImage1* d = dynamic_cast<DImage1*>(dat[0]);

    Mat img = d->getImage();
    Mat out;

    int value = dialog.getValue();
    int type = dialog.getType();

    threshold(img, out, value, 255, type);

    DImage1* o = new DImage1();
    o->setImage(out);

    ans.push_back(o);

    return ans;
}

static FilterFactory<FThreshold> fThreshold;
