#include "fdistance.h"

/*****************************************************************************
 *
 *****************************************************************************/
FDistance::FDistance(QObject* parent) :
    Filter(parent)
{
}

FDistance::~FDistance()
{

}

/*****************************************************************************
 *
 *****************************************************************************/
QString FDistance::getName()
{
    return QString("Magnitude");
}

/*****************************************************************************
 *
 *****************************************************************************/
QString FDistance::getCaption()
{
    return QString("Magnitude");
}

/*****************************************************************************
 *
 *****************************************************************************/
QVector<DatInfo> FDistance::getInputTypes()
{
    QVector<DatInfo> ans;
    ans.push_back(DatInfo(IMAGE1,"Input Image"));
    ans.push_back(DatInfo(IMAGE1, "Input Image"));
    return ans;
}

/*****************************************************************************
 *
 *****************************************************************************/
QVector<DatInfo> FDistance::getOutputTypes()
{
    QVector<DatInfo> ans;
    ans.push_back(DatInfo(IMAGE1, "Output"));
    return ans;
}

/*****************************************************************************
 *
 *****************************************************************************/
void FDistance::showConfig()
{
    dialog.exec();
}

/*****************************************************************************
 *
 *****************************************************************************/
QMap<QString, QVariant> FDistance::getData()
{
    QMap<QString, QVariant> ans;
    ans.insert("Name", QVariant(getName()));

    FDistanceDialog::FDISTANCE dist = dialog.getType();

    QString type;
    switch(dist)
    {
        case FDistanceDialog::DIST_EUCLIDEAN:
            type = "Euclidean";
            break;
        case FDistanceDialog::DIST_MANHATTAN:
            type = "Manhattan";
            break;
        case FDistanceDialog::DIST_CHEBYSHEV:
            type = "Chebyshev";
            break;
    }

    ans.insert("Type", QVariant(type));

    return ans;
}

/*****************************************************************************
 * Sets the properties of the filter.
 * Filter type - The type of algorithm to use when calculating distance
 *****************************************************************************/
void FDistance::setData(QMap<QString, QVariant> data)
{
    FDistanceDialog::FDISTANCE dist = FDistanceDialog::DIST_EUCLIDEAN;
    if (data.contains("Type"))
    {
        if (data["Type"] == "Euclidean")
        {
            dist = FDistanceDialog::DIST_EUCLIDEAN;
        }
        else if (data["Type"] == "Manhattan")
        {
            dist = FDistanceDialog::DIST_MANHATTAN;
        }
        else if (data["Type"] == "Chebyshev")
        {
            dist = FDistanceDialog::DIST_CHEBYSHEV;
        }
    }
    dialog.setType(dist);
}

/*****************************************************************************
 *
 *****************************************************************************/
void FDistance::reset()
{

}

/*****************************************************************************
 * Calculates the distance between the values of both channels using the
 * selected algorithm
 *****************************************************************************/
QVector<Data*> FDistance::run(QVector<Data*> dat)
{
    DImage1* img1 = dynamic_cast<DImage1*>(dat[0]);
    DImage1* img2 = dynamic_cast<DImage1*>(dat[1]);

    FDistanceDialog::FDISTANCE dist = dialog.getType();

    Mat mimg1 = img1->getImage();
    Mat mimg2 = img2->getImage();

    Mat dst = Mat::zeros(mimg1.rows, mimg1.cols, CV_8UC1);

    //Euclidean sqrt(a^2 + b^2)
    if (dist == FDistanceDialog::DIST_EUCLIDEAN)
    {
        for (int y = 0; y < mimg1.rows; y++)
        {
            for (int x = 0; x < mimg1.cols; x++)
            {
                int d1 = mimg1.at<unsigned char>(y,x);
                int d2 = mimg2.at<unsigned char>(y,x);
                dst.at<unsigned char>(y,x) = sqrt(d1+d2);
            }
        }
    }
    //Manhattan (a - b)
    else if (dist == FDistanceDialog::DIST_MANHATTAN)
    {
        for (int y = 0; y < mimg1.rows; y++)
        {
            for (int x = 0; x < mimg1.cols; x++)
            {
                int d1 = mimg1.at<unsigned char>(y,x);
                int d2 = mimg2.at<unsigned char>(y,x);
                dst.at<unsigned char>(y,x) = abs(d1-d2);
            }
        }
    }
    else //Chebyshev (DONT KNOW IF I AM CALCULATING THIS ONE CORRECTLY)
    {
        for (int y = 0; y < mimg1.rows; y++)
        {
            for (int x = 0; x < mimg1.cols; x++)
            {
                int d1 = mimg1.at<unsigned char>(y,x);
                int d2 = mimg2.at<unsigned char>(y,x);
                dst.at<unsigned char>(y,x) = max(d1,d2);
            }
        }
    }

    DImage1* out = new DImage1();
    out->setImage(dst);

    QVector<Data*> ans;
    ans.push_back(out);
    return ans;
}

static FilterFactory<FDistance> fDistance;
