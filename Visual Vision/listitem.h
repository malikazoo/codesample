/*****************************************************************************
 * Copyright Tim Price
 *****************************************************************************/

#ifndef LISTITEM_H
#define LISTITEM_H

#include <QAbstractGraphicsShapeItem>
#include <QPainter>

/*****************************************************************************
 * An item to show in the list
 *****************************************************************************/
class ListItem : public QAbstractGraphicsShapeItem
{
    public:
        ListItem();

        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
        virtual QRectF boundingRect() const;
        int type() const;
        void setPosY(int y);
        void setText(QString text);
        void setAsTitle(bool istitle);
        bool isTitle();

    private:
        QRectF vrect;
        enum { Type = UserType + 4 };
        QString vText;

        bool vIsTitle;
};

#endif // LISTITEM_H
