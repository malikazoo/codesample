#include "fdisplayhistogram.h"

/*****************************************************************************
 *
 *****************************************************************************/
FDisplayHistogram::FDisplayHistogram(QObject *parent) :
    Filter(parent)
{
}

/*****************************************************************************
 *
 *****************************************************************************/
QString FDisplayHistogram::getName()
{
    return QString("Draw Histogram");
}

/*****************************************************************************
 *
 *****************************************************************************/
QString FDisplayHistogram::getCaption()
{
    return QString("Draw Histogram");
}

/*****************************************************************************
 *
 *****************************************************************************/
QVector<DatInfo> FDisplayHistogram::getInputTypes()
{
    QVector<DatInfo> ans;

    ans.push_back(DatInfo(HISTOGRAM, "Input Histogram"));

    return ans;
}

/*****************************************************************************
 *
 *****************************************************************************/
QVector<DatInfo> FDisplayHistogram::getOutputTypes()
{
    QVector<DatInfo> ans;
    ans.push_back(DatInfo(IMAGE3, "Output Image"));
    return ans;
}

/*****************************************************************************
 *
 *****************************************************************************/
void FDisplayHistogram::showConfig()
{
    dialog.exec();
}

/*****************************************************************************
 *
 *****************************************************************************/
QMap<QString, QVariant> FDisplayHistogram::getData()
{
    QMap<QString, QVariant> ans;
    ans.insert("Name", QVariant(getName()));

    QColor backColor = dialog.getBackColor();
    QColor foreColor = dialog.getForeColor();
    int height = dialog.getHeight();
    int width = dialog.getWidth();

    ans.insert("BackColor", QVariant(backColor.name()));
    ans.insert("ForeColor", QVariant(foreColor.name()));
    ans.insert("Width", QVariant(width));
    ans.insert("Height", QVariant(height));

    return ans;

}

/*****************************************************************************
 *
 *****************************************************************************/
void FDisplayHistogram::setData(QMap<QString, QVariant> data)
{
    if (data.contains("BackColor"))
    {
        QColor bkcol = QColor(data["BackColor"].toString());
        dialog.setBackColor(bkcol);
    }

    if (data.contains("ForeColor"))
    {
        QColor frcol = QColor(data["ForeColor"].toString());
        dialog.setForeColor(frcol);
    }

    if (data.contains("Width"))
    {
        dialog.setWidth(data["Width"].toInt());
    }

    if (data.contains("Height"))
    {
        dialog.setHeight(data["Height"].toInt());
    }

}

/*****************************************************************************
 *
 *****************************************************************************/
void FDisplayHistogram::reset()
{

}

/*****************************************************************************
 *
 *****************************************************************************/
QVector<Data*> FDisplayHistogram::run(QVector<Data*> dat)
{
    QVector<Data*> ans;

    DHistogram* hist = dynamic_cast<DHistogram*>(dat[0]);

    QVector<int> d = hist->getData();
    int width = dialog.getWidth();
    int height = dialog.getHeight();
    int maxval = hist->getMaxValue();
    QColor backcolor = dialog.getBackColor();
    QColor forecolor = dialog.getForeColor();
    Mat o(height, width, CV_8UC3, Scalar(0,0,0));

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            o.at<Vec3b>(y,x) = Vec3b(backcolor.blue(), backcolor.green(), backcolor.red());
        }
    }

    for (int i = 0; i < d.size(); i++)
    {
        int wstart = (double)width / d.size() * i;
        int wend = ((double)width / d.size() * (i + 1)) - 1;
        int he = (double)height / maxval * d[i];

        for (int w = wstart; w <= wend; w++)
        {
            for (int h = height-1; h >= height-he; h--)
            {
                o.at<Vec3b>(h,w) = Vec3b(forecolor.blue(), forecolor.green(), forecolor.red());
            }
        }
    }


    DImage3* out = new DImage3();
    out->setImage(o);
    ans.push_back(out);
    return ans;

}

static FilterFactory<FDisplayHistogram> fDisplayHistogram;
