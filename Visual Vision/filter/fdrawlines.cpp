#include "fdrawlines.h"

/*****************************************************************************
 *
 *****************************************************************************/
FDrawLines::FDrawLines(QObject* parent) :
    Filter(parent)
{
}

/*****************************************************************************
 *
 *****************************************************************************/
FDrawLines::~FDrawLines()
{

}

/*****************************************************************************
 *
 *****************************************************************************/
QString FDrawLines::getName()
{
    return QString("Draw Lines");
}

/*****************************************************************************
 *
 *****************************************************************************/
QString FDrawLines::getCaption()
{
    return QString("Draw Lines");
}

/*****************************************************************************
 *
 *****************************************************************************/
QVector<DatInfo> FDrawLines::getInputTypes()
{
    QVector<DatInfo> ans;

    ans.push_back(DatInfo(IMAGE3, "Input Image"));
    ans.push_back(DatInfo(LINE, "Input Lines"));
    return ans;
}

/*****************************************************************************
 *
 *****************************************************************************/
QVector<DatInfo> FDrawLines::getOutputTypes()
{
    QVector<DatInfo> ans;

    ans.push_back(DatInfo(IMAGE3, "Output Image"));

    return ans;
}

/*****************************************************************************
 *
 *****************************************************************************/
void FDrawLines::showConfig()
{
    dialog.exec();
}

/*****************************************************************************
 *
 *****************************************************************************/
QMap<QString, QVariant> FDrawLines::getData()
{
    QMap<QString, QVariant> ans;
    ans.insert("Name", QVariant(getName()));

    QColor c = dialog.getSelectedColor();
    int width = dialog.getWidth();

    ans.insert("Color", QVariant(c.name()));
    ans.insert("Width", QVariant(width));

    return ans;

}

/*****************************************************************************
 *
 *****************************************************************************/
void FDrawLines::setData(QMap<QString, QVariant> data)
{
    if (data.contains("Color"))
    {
        QColor col(data["Color"].toString());
        dialog.setColor(col);
    }

    if (data.contains("Width"))
    {
        dialog.setWidth(data["Width"].toInt());
    }
}

/*****************************************************************************
 *
 *****************************************************************************/
void FDrawLines::reset()
{

}

/*****************************************************************************
 *
 *****************************************************************************/
QVector<Data*> FDrawLines::run(QVector<Data*> dat)
{
    DImage3* img = dynamic_cast<DImage3*>(dat[0]);
    DLine* lin = dynamic_cast<DLine*>(dat[1]);

    Mat src = img->getImage();
    Mat dst = src.clone();

    QColor co = dialog.getSelectedColor();

    QVector<QLineF> lines = lin->getLines();

    for (int i = 0; i < lines.size(); i++)
    {
        QLineF f = lines[i];
        line(dst,Point(f.x1(), f.y1()), Point(f.x2(), f.y2()), Scalar(co.blue(), co.green(), co.red()), dialog.getWidth());
    }


    DImage3* d = new DImage3();
    d->setImage(dst);
    QVector<Data*> ans;
    ans.push_back(d);
    return ans;
}

static FilterFactory<FDrawLines> fDrawLines;
