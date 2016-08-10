#include "listitem.h"

/*****************************************************************************
 *
 *****************************************************************************/
ListItem::ListItem()
{
    vrect = QRectF(0,0,180,15);
    vIsTitle = false;
}

/*****************************************************************************
 *
 *****************************************************************************/
void ListItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    //painter->setPen(QPen(Qt::red));
    //painter->drawRoundedRect(vrect,3,3);
    if (vIsTitle)
    {
        //painter->setBackgroundMode(Qt::OpaqueMode);
        //painter->setBackground(QBrush(QColor(80,80,80)));
        painter->fillRect(vrect,QBrush(QColor(60,60,60)));
        painter->setPen(QColor(Qt::white));
    }
    else
    {
        painter->fillRect(vrect, QBrush(QColor(Qt::white)));
        painter->setPen(QColor(Qt::black));
    }

    painter->drawText(vrect,vText);
}

/*****************************************************************************
 *
 *****************************************************************************/
QRectF ListItem::boundingRect() const
{
    return vrect;
}

/*****************************************************************************
 *
 *****************************************************************************/
int ListItem::type() const
{
    return Type;
}

/*****************************************************************************
 *
 *****************************************************************************/
void ListItem::setPosY(int y)
{
    vrect = QRectF(0,y,180,15);
}

/*****************************************************************************
 *
 *****************************************************************************/
void ListItem::setText(QString text)
{
    vText = text;
}

/*****************************************************************************
 *
 *****************************************************************************/
void ListItem::setAsTitle(bool istitle)
{
    vIsTitle = istitle;
}

/*****************************************************************************
 *
 *****************************************************************************/
bool ListItem::isTitle()
{
    return vIsTitle;
}

