#include "fdrawcircle.h"

/*****************************************************************************
 *
 *****************************************************************************/
FDrawCircle::FDrawCircle(QObject* parent) :
    Filter(parent)
{
}

FDrawCircle::~FDrawCircle()
{

}

/*****************************************************************************
 *
 *****************************************************************************/
QString FDrawCircle::getName()
{
    return QString("Draw Circle");
}

/*****************************************************************************
 *
 *****************************************************************************/
QString FDrawCircle::getCaption()
{
    return QString("Draw Circle");
}

/*****************************************************************************
 *
 *****************************************************************************/
QVector<DatInfo> FDrawCircle::getInputTypes()
{
    QVector<DatInfo> ans;

    ans.push_back(DatInfo(IMAGE3, "Image"));
    ans.push_back(DatInfo(CIRCLE, "Circles"));

    return ans;
}

/*****************************************************************************
 *
 *****************************************************************************/
QVector<DatInfo> FDrawCircle::getOutputTypes()
{
    QVector<DatInfo> ans;
    ans.push_back(DatInfo(IMAGE3, "Image"));
    return ans;
}

/*****************************************************************************
 *
 *****************************************************************************/
void FDrawCircle::showConfig()
{
    dialog.exec();
}

/*****************************************************************************
 *
 *****************************************************************************/
QMap<QString, QVariant> FDrawCircle::getData()
{
    QMap<QString, QVariant> ans;
    ans.insert("Name", QVariant(getName()));

    QColor c = dialog.getColor();
    int width = dialog.getWidth();

    ans.insert("Color", QVariant(c.name()));
    ans.insert("Width", width);

    return ans;

}

/*****************************************************************************
 *
 *****************************************************************************/
void FDrawCircle::setData(QMap<QString, QVariant> data)
{
    if (data.contains("Color"))
    {
        QString c = data["Color"].toString();
        QColor col(c);
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
void FDrawCircle::reset()
{

}

/*****************************************************************************
 *
 *****************************************************************************/
QVector<Data*> FDrawCircle::run(QVector<Data*> dat)
{
    DImage3* img = dynamic_cast<DImage3*>(dat[0]);
    Circle* c = dynamic_cast<Circle*>(dat[1]);

    Point p;
    p.x = c->point.x();
    p.y = c->point.y();

    QColor co = dialog.getColor();

    Mat i = img->getImage().clone();
    circle(i,p,c->radius,Scalar(co.blue(), co.green(), co.red()), dialog.getWidth());

    QVector<Data*> ans;

    DImage3* a = new DImage3();
    a->setImage(i);

    ans.push_back(a);

    return ans;

}

static FilterFactory<FDrawCircle> fDrawCircle;
