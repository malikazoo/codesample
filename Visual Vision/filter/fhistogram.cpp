#include "fhistogram.h"

/*****************************************************************************
 *
 *****************************************************************************/
FHistogram::FHistogram(QObject *parent) :
    Filter(parent)
{
}

/*****************************************************************************
 *
 *****************************************************************************/
FHistogram::~FHistogram()
{

}

/*****************************************************************************
 *
 *****************************************************************************/
QString FHistogram::getName()
{
    return QString("Generate Histogram");
}

/*****************************************************************************
 *
 *****************************************************************************/
QString FHistogram::getCaption()
{
    return QString("Histogram");
}

/*****************************************************************************
 *
 *****************************************************************************/
QVector<DatInfo> FHistogram::getInputTypes()
{
    QVector<DatInfo> ans;

    ans.push_back(DatInfo(IMAGE1,"Input Image"));

    return ans;
}

/*****************************************************************************
 *
 *****************************************************************************/
QVector<DatInfo> FHistogram::getOutputTypes()
{
    QVector<DatInfo> ans;

    ans.push_back(DatInfo(HISTOGRAM, "Output"));

    return ans;
}

/*****************************************************************************
 *
 *****************************************************************************/
void FHistogram::showConfig()
{

}

/*****************************************************************************
 *
 *****************************************************************************/
QMap<QString, QVariant> FHistogram::getData()
{
    QMap<QString, QVariant> ans;
    ans.insert("Name", QVariant(getName()));


    return ans;
}

/*****************************************************************************
 *
 *****************************************************************************/
void FHistogram::setData(QMap<QString, QVariant> data)
{

}

/*****************************************************************************
 *
 *****************************************************************************/
void FHistogram::reset()
{

}

/*****************************************************************************
 *
 *****************************************************************************/
QVector<Data*> FHistogram::run(QVector<Data*> dat)
{
    QVector<Data*> ans;

    DImage1* img = dynamic_cast<DImage1*>(dat[0]);

    Mat i = img->getImage();

    QVector<int> out(256);
    for (int i = 0; i < out.size(); i++)
    {
        out[i] = 0;
    }

    for (int y = 0; y < i.rows; y++)
    {
        for (int x = 0; x < i.cols; x++)
        {
            out[i.at<unsigned char>(y,x)]++;
        }
    }

    DHistogram* o = new DHistogram();
    o->setData(out);
    ans.push_back(o);

    return ans;
}

static FilterFactory<FHistogram> fHistogram;
