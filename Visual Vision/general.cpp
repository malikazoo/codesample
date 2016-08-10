#include "general.h"

/*****************************************************************************
 *
 *****************************************************************************/
QImage getImage(DatType type)
{
    switch(type)
    {
        case NONE:
            return QImage(":/data/none.png");
            break;
        case IMAGE3:
            return QImage(":/data/3channel.png");
            break;
        case IMAGE1:
            return QImage(":/data/1channel.png");
            break;
        case POINT:
            return QImage(":/data/point.png");
            break;
        case LINE:
            return QImage(":/data/line.png");
            break;
        case REAL:
            return QImage(":/data/real.png");
            break;
        case INT:
            return QImage(":/data/int.png");
            break;
        case CIRCLE:
            return QImage(":/data/circle.png");
            break;
        case MATRIX:
            return QImage(":/data/matrix.png");
            break;
        case LIST:
            return QImage(":/data/list.png");
            break;
        case HISTOGRAM:
            return QImage(":/data/histogram.png");
            break;
        case SIZE:
            return QImage(":/data/size.png");
            break;

    }

    return QImage();
}

/*****************************************************************************
 *
 *****************************************************************************/
void outputDatType(DatType type)
{
    switch (type)
    {
        case IMAGE1:
            qDebug() << "Image1";
            break;
        case IMAGE3:
            qDebug() << "Image3";
            break;
        case POINT:
            qDebug() << "Point";
            break;
        case LINE:
            qDebug() << "Line";
            break;
        case NONE:
            qDebug() << "None";
            break;
        case CIRCLE:
            qDebug() << "Circle";
            break;
        case REAL:
            qDebug() << "Real";
            break;
        case INT:
            qDebug() << "Int";
            break;
        case MATRIX:
            qDebug() << "Matrix";
            break;
        case LIST:
            qDebug() << "List";
            break;
        case HISTOGRAM:
            qDebug() << "Histogram";
            break;
        case SIZE:
            qDebug() << "Size";
            break;
    }
}


/*****************************************************************************
 *
 *****************************************************************************/
DatInfo::DatInfo()
{
    type = NONE;
    label = "";
    required = true;
}

/*****************************************************************************
 *
 *****************************************************************************/
DatInfo::DatInfo(DatType t, QString l, bool isRequired)
{
    type = t;
    label = l;
    required = isRequired;
}

/*****************************************************************************
 *
 *****************************************************************************/
Circle::Circle()
{
    this->radius = 0;
}

/*****************************************************************************
 *
 *****************************************************************************/
Circle::Circle(QPointF pnt, double radius)
{
    point = pnt;
    this->radius = radius;
}

/*****************************************************************************
 *
 *****************************************************************************/
FiltList::FiltList(QString name, QString icon)
{
    this->name = name;
    this->icon = icon;
}
