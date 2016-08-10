#include "fhoughcircle.h"

/*****************************************************************************
 *
 *****************************************************************************/
FHoughCircle::FHoughCircle(QObject *parent) :
    Filter(parent)
{
}

/*****************************************************************************
 *
 *****************************************************************************/
FHoughCircle::~FHoughCircle()
{

}

/*****************************************************************************
 *
 *****************************************************************************/
QString FHoughCircle::getName()
{
    return QString("Hough Circle");
}

/*****************************************************************************
 *
 *****************************************************************************/
QString FHoughCircle::getCaption()
{
    return QString("Hough Circle");
}

/*****************************************************************************
 *
 *****************************************************************************/
QVector<DatInfo> FHoughCircle::getInputTypes()
{
    QVector<DatInfo> ans;
    ans.push_back(DatInfo(IMAGE1, "Image"));
    return ans;
}

/*****************************************************************************
 *
 *****************************************************************************/
QVector<DatInfo> FHoughCircle::getOutputTypes()
{
    QVector<DatInfo> ans;
    ans.push_back(DatInfo(CIRCLE, "Detected Circles"));
    return ans;
}

/*****************************************************************************
 *
 *****************************************************************************/
void FHoughCircle::showConfig()
{
    dialog.show();
}

/*****************************************************************************
 *
 *****************************************************************************/
QMap<QString, QVariant> FHoughCircle::getData()
{
    QMap<QString, QVariant> ans;
    ans.insert("Name", QVariant(getName()));

    ans.insert("Param1", QVariant(dialog.param1()));
    ans.insert("Param2", QVariant(dialog.param2()));
    ans.insert("MinRadius", QVariant(dialog.minRadius()));
    ans.insert("MaxRadius", QVariant(dialog.maxRadius()));
    ans.insert("MinDistance", QVariant(dialog.minDistance()));

    return ans;
}

/*****************************************************************************
 *
 *****************************************************************************/
void FHoughCircle::setData(QMap<QString, QVariant> data)
{
    if (data.contains("Param1"))
    {
        dialog.setParam1(data["Param1"].toDouble());
    }

    if (data.contains("Param2"))
    {
        dialog.setParam2(data["Param2"].toDouble());
    }

    if (data.contains("MinRadius"))
    {
        dialog.setMinRadius(data["MinRadius"].toInt());
    }

    if (data.contains("MaxRadius"))
    {
        dialog.setMaxRadius(data["MaxRadius"].toInt());
    }

    if (data.contains("MinDistance"))
    {
        dialog.setMinDistance(data["MinDistance"].toInt());
    }

}

/*****************************************************************************
 *
 *****************************************************************************/
void FHoughCircle::reset()
{

}

/*****************************************************************************
 *
 *****************************************************************************/
QVector<Data*> FHoughCircle::run(QVector<Data*> dat)
{
    QVector<Data*> ans;
    DImage1* d = dynamic_cast<DImage1*>(dat[0]);

    vector<Vec3f> dst;

    Mat img = d->getImage();

    HoughCircles(img,dst,CV_HOUGH_GRADIENT,1,dialog.minDistance(),dialog.param1(),dialog.param2(),dialog.minRadius(),dialog.maxRadius());

    DCircle* out = new DCircle();

    QVector<Circle> outData;
    for (int i = 0; i < dst.size(); i++)
    {
        outData.push_back(Circle(QPointF(dst[i][0], dst[i][1]), dst[i][2]));
    }

    out->setData(outData);

    ans.push_back(out);
    return ans;

}

static FilterFactory<FHoughCircle> fHoughCircle;
