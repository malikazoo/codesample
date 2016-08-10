#include "fresize.h"

/*****************************************************************************
 *
 *****************************************************************************/
FResize::FResize(QObject *parent) :
    Filter(parent)
{
}

/*****************************************************************************
 *
 *****************************************************************************/
FResize::~FResize()
{

}

/*****************************************************************************
 *
 *****************************************************************************/
QString FResize::getName()
{
    return QString("Resize");
}

/*****************************************************************************
 *
 *****************************************************************************/
QString FResize::getCaption()
{
    return QString("Resize");
}

/*****************************************************************************
 *
 *****************************************************************************/
QVector<DatInfo> FResize::getInputTypes()
{
    QVector<DatInfo> ans;

    ans.push_back(DatInfo(IMAGE3,"Image"));

    return ans;
}

/*****************************************************************************
 *
 *****************************************************************************/
QVector<DatInfo> FResize::getOutputTypes()
{
    QVector<DatInfo> ans;

    ans.push_back(DatInfo(IMAGE3, "Image"));

    return ans;
}

/*****************************************************************************
 *
 *****************************************************************************/
void FResize::showConfig()
{
    dialog.exec();
}

/*****************************************************************************
 *
 *****************************************************************************/
QMap<QString, QVariant> FResize::getData()
{
    QMap<QString, QVariant> ans;
    ans.insert("Name", QVariant(getName()));

    ans.insert("SizeX", QVariant(dialog.getX()));
    ans.insert("SizeY", QVariant(dialog.getY()));

    return ans;
}

/*****************************************************************************
 *
 *****************************************************************************/
void FResize::setData(QMap<QString, QVariant> data)
{
    if (data.contains("SizeX"))
    {
        dialog.setX(data["SizeX"].toInt());
    }

    if (data.contains("SizeY"))
    {
        dialog.setY(data["SizeY"].toInt());
    }
}

/*****************************************************************************
 *
 *****************************************************************************/
void FResize::reset()
{

}

/*****************************************************************************
 *
 *****************************************************************************/
QVector<Data*> FResize::run(QVector<Data*> dat)
{
    QVector<Data*> ans;

    DImage3* img = dynamic_cast<DImage3*>(dat[0]);

    Mat src;
    Mat dst;
    src = img->getImage();

    int xsize = dialog.getX();
    int ysize = dialog.getY();

    resize(src,dst, Size(xsize,ysize));

    DImage3* a = new DImage3();

    a->setImage(dst);

    ans.push_back(a);
    return ans;
}

static FilterFactory<FResize> fResize;
