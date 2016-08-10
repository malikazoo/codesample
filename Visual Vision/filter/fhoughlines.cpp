#include "fhoughlines.h"

/*****************************************************************************
 *
 *****************************************************************************/
FHoughLines::FHoughLines(QObject *parent) :
    Filter(parent)
{
}

/*****************************************************************************
 *
 *****************************************************************************/
FHoughLines::~FHoughLines()
{

}

/*****************************************************************************
 *
 *****************************************************************************/
QString FHoughLines::getName()
{
    return QString("Hough Line");
}

/*****************************************************************************
 *
 *****************************************************************************/
QString FHoughLines::getCaption()
{
    return QString("Hough Line");
}

/*****************************************************************************
 *
 *****************************************************************************/
QVector<DatInfo> FHoughLines::getInputTypes()
{
    QVector<DatInfo> ans;

    ans.push_back(DatInfo(IMAGE1, "Input Image"));

    return ans;
}

/*****************************************************************************
 *
 *****************************************************************************/
QVector<DatInfo> FHoughLines::getOutputTypes()
{
    QVector<DatInfo> ans;

    ans.push_back(DatInfo(LINE, "Lines"));

    return ans;
}

/*****************************************************************************
 *
 *****************************************************************************/
void FHoughLines::showConfig()
{
    dialog.exec();
}

/*****************************************************************************
 *
 *****************************************************************************/
QMap<QString, QVariant> FHoughLines::getData()
{
    QMap<QString, QVariant> ans;
    ans.insert("Name", QVariant(getName()));

    ans.insert("Rho", QVariant(dialog.getRho()));
    ans.insert("Theta", QVariant(dialog.getTheta()));
    ans.insert("Threshold", QVariant(dialog.getThreshold()));
    ans.insert("MinLineLength", QVariant(dialog.getMinLineLength()));
    ans.insert("MaxLineGap", QVariant(dialog.getMaxLineGap()));

    return ans;
}

/*****************************************************************************
 *
 *****************************************************************************/
void FHoughLines::setData(QMap<QString, QVariant> data)
{
    if (data.contains("Rho"))
    {
        dialog.setRho(data["Rho"].toDouble());
    }

    if (data.contains("Theta"))
    {
        dialog.setTheta(data["Theta"].toDouble());
    }

    if (data.contains("Threshold"))
    {
        dialog.setThreshold(data["Threshold"].toInt());
    }

    if (data.contains("MinLineLength"))
    {
        dialog.setMinLineLength(data["MinLineLength"].toDouble());
    }

    if (data.contains("MaxLineGap"))
    {
        dialog.setMaxLineGap(data["MaxLineGap"].toDouble());
    }

}

/*****************************************************************************
 *
 *****************************************************************************/
void FHoughLines::reset()
{

}

/*****************************************************************************
 *
 *****************************************************************************/
QVector<Data*> FHoughLines::run(QVector<Data*> dat)
{
    DImage1* d = dynamic_cast<DImage1*>(dat[0]);
    Mat img = d->getImage();
    QVector<QLineF> dst;

    vector<Vec4i> vout;
    HoughLinesP(img,vout,dialog.getRho(), dialog.getTheta(), dialog.getThreshold(), dialog.getMinLineLength(), dialog.getMaxLineGap());

    for (int i = 0; i < vout.size(); i++)
    {
        dst.push_back(QLineF(vout[i][0], vout[i][1], vout[i][2], vout[i][3]));
    }

    DLine* out = new DLine();
    out->setLines(dst);

    QVector<Data*> ans;
    ans.push_back(out);
    return ans;
}

static FilterFactory<FHoughLines> fHoughLines;
