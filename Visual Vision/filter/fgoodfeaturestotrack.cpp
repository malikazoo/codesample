#include "fgoodfeaturestotrack.h"

FGoodFeaturesToTrack::FGoodFeaturesToTrack(QObject *parent) :
    Filter(parent)
{
}

QString FGoodFeaturesToTrack::getName()
{
    return QString("Good Features To Track");
}

QString FGoodFeaturesToTrack::getCaption()
{
    return QString("Good Features");
}

QVector<DatInfo> FGoodFeaturesToTrack::getInputTypes()
{
    QVector<DatInfo> ans;
    ans.push_back(DatInfo(IMAGE1, "Input Image"));
    return ans;
}

QVector<DatInfo> FGoodFeaturesToTrack::getOutputTypes()
{
    QVector<DatInfo> ans;
    ans.push_back(DatInfo(POINT, "Output Points"));
    return ans;
}

void FGoodFeaturesToTrack::showConfig()
{
    dialog.exec();
}

QMap<QString, QVariant> FGoodFeaturesToTrack::getData()
{
    QMap<QString, QVariant> ans;

    ans["Quality"] = QVariant(dialog.getQuality());
    ans["MinDistance"] = QVariant(dialog.getMinDistance());
    ans["MaxCorners"] = QVariant(dialog.getMaxCorners());

    return ans;
}

void FGoodFeaturesToTrack::setData(QMap<QString, QVariant> data)
{
    if (data.contains("Quality"))
    {
        dialog.setQuality(data["Quality"].toDouble());
    }

    if (data.contains("MinDistance"))
    {
        dialog.setMinDistance(data["MinDistance"].toDouble());
    }

    if (data.contains("MaxCorners"))
    {
        dialog.setMaxCorners(data["MaxCorners"].toInt());
    }

}

void FGoodFeaturesToTrack::reset()
{

}

QVector<Data*> FGoodFeaturesToTrack::run(QVector<Data*> dat)
{
    QVector<Data*> ans;

    DImage1* d = dynamic_cast<DImage1*>(dat[0]);

    Mat inimg = d->getImage();
    vector<Point2f> pnts;

    goodFeaturesToTrack(inimg,pnts,dialog.getMaxCorners(),dialog.getQuality(),dialog.getMinDistance());

    //cornerSubPix(inimg,pnts,);


    DPoint* p = new DPoint();
    QVector<QPointF> points;


    for (int i = 0; i < pnts.size(); i++)
    {
        points.push_back(QPointF(pnts[i].x, pnts[i].y));
    }

    p->setPoints(points);

    ans.push_back(p);

    return ans;
}

static FilterFactory<FGoodFeaturesToTrack> fGoodFeaturesToTrack;
