#include "fcolor.h"

/*****************************************************************************
 *
 *****************************************************************************/
FColor::FColor(QObject* parent) : Filter(parent)
{

}

/*****************************************************************************
 *
 *****************************************************************************/
FColor::~FColor()
{

}

/*****************************************************************************
 *
 *****************************************************************************/
QString FColor::getName()
{
    return QString("Grayscale to Color");
}

/*****************************************************************************
 *
 *****************************************************************************/
QString FColor::getCaption()
{
    return QString("Color");
}

/*****************************************************************************
 *
 *****************************************************************************/
QVector<DatInfo> FColor::getInputTypes()
{
    QVector<DatInfo> ans;
    ans.push_back(DatInfo(IMAGE1, "Grayscale Image"));
    return ans;
}

/*****************************************************************************
 *
 *****************************************************************************/
QVector<DatInfo> FColor::getOutputTypes()
{
    QVector<DatInfo> ans;
    ans.push_back(DatInfo(IMAGE3, "Color Image"));
    return ans;
}

/*****************************************************************************
 *
 *****************************************************************************/
void FColor::showConfig()
{
    dialog.exec();
}

/*****************************************************************************
 *
 *****************************************************************************/
QMap<QString, QVariant> FColor::getData()
{
    QMap<QString, QVariant> ans;

    ans.insert("Name", QVariant(getName()));
    ans.insert("Red", QVariant(dialog.amountRed()));
    ans.insert("Green", QVariant(dialog.amountGreen()));
    ans.insert("Blue", QVariant(dialog.amountBlue()));

    return ans;

}

/*****************************************************************************
 *
 *****************************************************************************/
void FColor::setData(QMap<QString, QVariant> data)
{
    if (data.contains("Red"))
    {
        dialog.setRed(data["Red"].toDouble());
    }
    if (data.contains("Green"))
    {
        dialog.setGreen(data["Green"].toDouble());
    }
    if (data.contains("Blue"))
    {
        dialog.setBlue(data["Blue"].toDouble());
    }
}

/*****************************************************************************
 *
 *****************************************************************************/
void FColor::reset()
{

}

/*****************************************************************************
 *
 *****************************************************************************/
QVector<Data*> FColor::run(QVector<Data*> dat)
{
    QVector<Data*> ans;
    DImage1* d = dynamic_cast<DImage1*>(dat[0]);

    Mat inimg = d->getImage();

    Mat oimg(inimg.rows,inimg.cols, CV_8UC3);

    for (int y = 0; y < inimg.rows; y++)
    {
        for (int x = 0; x < inimg.cols; x++)
        {
            unsigned char c = inimg.at<unsigned char>(y,x);
            double d = c / 100.0;
            oimg.at<Vec3b>(y,x) = Vec3b(d * dialog.amountBlue(), d * dialog.amountGreen(), d * dialog.amountRed());
        }
    }

    DImage3* out = new DImage3();
    out->setImage(oimg);

    ans.push_back(out);

    return ans;
}

static FilterFactory<FColor> fColor;
