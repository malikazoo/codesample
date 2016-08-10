#include "fcanny.h"

/*****************************************************************************
 *
 *****************************************************************************/
FCanny::FCanny(QObject* parent) :
    Filter(parent)
{
}

FCanny::~FCanny()
{

}

/*****************************************************************************
 *
 *****************************************************************************/
QString FCanny::getName()
{
    return QString("Canny");
}

/*****************************************************************************
 *
 *****************************************************************************/
QString FCanny::getCaption()
{
    return QString("Canny");
}

/*****************************************************************************
 *
 *****************************************************************************/
QVector<DatInfo> FCanny::getInputTypes()
{
    QVector<DatInfo> ans;

    ans.push_back(DatInfo(IMAGE1, "Input"));

    return ans;
}

/*****************************************************************************
 *
 *****************************************************************************/
QVector<DatInfo> FCanny::getOutputTypes()
{
    QVector<DatInfo> ans;

    ans.push_back(DatInfo(IMAGE1, "Output"));

    return ans;
}

/*****************************************************************************
 *
 *****************************************************************************/
void FCanny::showConfig()
{
    dialog.show();
}

/*****************************************************************************
 *
 *****************************************************************************/
QMap<QString, QVariant> FCanny::getData()
{
    QMap<QString, QVariant> ans;
    ans.insert("Name", QVariant(getName()));
    int k = dialog.getKernelSize();
    double thresh1 = dialog.getThresh1();
    double thresh2 = dialog.getThresh2();

    ans.insert("Kernel", QVariant(k));
    ans.insert("Thresh1", QVariant(thresh1));
    ans.insert("Thresh2", QVariant(thresh2));

    return ans;
}

/*****************************************************************************
 *
 *****************************************************************************/
void FCanny::setData(QMap<QString, QVariant> data)
{
    if (data.contains("Kernel"))
    {
        dialog.setKernelSize(data["Kernel"].toInt());
    }

    if (data.contains("Thresh1"))
    {
        dialog.setThresh1(data["Thresh1"].toDouble());
    }

    if (data.contains("Thresh2"))
    {
        dialog.setThresh2(data["Thresh2"].toDouble());
    }


}

/*****************************************************************************
 *
 *****************************************************************************/
void FCanny::reset()
{

}

/*****************************************************************************
 *
 *****************************************************************************/
QVector<Data*> FCanny::run(QVector<Data*> dat)
{
    DImage1* img = dynamic_cast<DImage1*>(dat[0]);

    Mat mimg = img->getImage();

    Mat dst;
    Canny(mimg,dst,dialog.getThresh1(), dialog.getThresh2(), dialog.getKernelSize());

    QVector<Data*> ans;

    DImage1* out = new DImage1();
    out->setImage(dst);
    ans.push_back(out);

    return ans;
}

static FilterFactory<FCanny> fCanny;
