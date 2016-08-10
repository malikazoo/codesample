#include "flaplacian.h"

/*****************************************************************************
 *
 *****************************************************************************/
FLaplacian::FLaplacian(QObject *parent) :
    Filter(parent)
{
}

/*****************************************************************************
 *
 *****************************************************************************/
FLaplacian::~FLaplacian()
{

}

/*****************************************************************************
 *
 *****************************************************************************/
QString FLaplacian::getName()
{
    return QString("Laplacian");
}

/*****************************************************************************
 *
 *****************************************************************************/
QString FLaplacian::getCaption()
{
    return QString("Laplacian");
}

/*****************************************************************************
 *
 *****************************************************************************/
QVector<DatInfo> FLaplacian::getInputTypes()
{
    QVector<DatInfo> ans;
    ans.push_back(DatInfo(IMAGE1, "Image"));
    return ans;

}

/*****************************************************************************
 *
 *****************************************************************************/
QVector<DatInfo> FLaplacian::getOutputTypes()
{
    QVector<DatInfo> ans;
    ans.push_back(DatInfo(IMAGE1, "Image"));
    return ans;

}

/*****************************************************************************
 *
 *****************************************************************************/
void FLaplacian::showConfig()
{

}

/*****************************************************************************
 *
 *****************************************************************************/
QMap<QString, QVariant> FLaplacian::getData()
{
    QMap<QString, QVariant> ans;
    ans.insert("Name", QVariant(getName()));

    ans.insert("Kernel", QVariant(dialog.getKernelSize()));

    return ans;

}

/*****************************************************************************
 *
 *****************************************************************************/
void FLaplacian::setData(QMap<QString, QVariant> data)
{
    if (data.contains("Kernel"))
    {
        dialog.setKernelSize(data["Kernel"].toInt());
    }
}

/*****************************************************************************
 *
 *****************************************************************************/
void FLaplacian::reset()
{

}

/*****************************************************************************
 *
 *****************************************************************************/
QVector<Data*> FLaplacian::run(QVector<Data*> dat)
{
    DImage1* d = dynamic_cast<DImage1*>(dat[0]);

    Mat sMat;

    int kernel_size = 3;
    int scale = 1;
    int delta = 0;

    Laplacian(d->getImage(), sMat, CV_16S, kernel_size, scale, delta, BORDER_DEFAULT);

    Mat abs;
    convertScaleAbs(sMat, abs);

    DImage1* a = new DImage1();
    a->setImage(abs);

    QVector<Data*> ans;
    ans.push_back(a);

    return ans;
}

static FilterFactory<FLaplacian> fLaplacian;
