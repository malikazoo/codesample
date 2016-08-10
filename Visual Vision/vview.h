/*****************************************************************************
 * Copyright Tim Price
 *****************************************************************************/

#ifndef VVIEW_H
#define VVIEW_H

#include <QAbstractGraphicsShapeItem>
#include <QGraphicsSceneHoverEvent>
#include <QPainter>
#include <QPointF>

#include "general.h"
#include "mapobj.h"

/*****************************************************************************
 * An input, output or filter item that gets put onto the canvas
 *****************************************************************************/
class VView : public QAbstractGraphicsShapeItem
{
    public:
        VView();

        void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*);
        QRectF boundingRect() const;
        void setRect(QRectF val);
        void setRect(float x, float y, float width, float height);
        int type() const;

        void setSelected(bool val);

        SelDat getClicked(QPointF p);

        QPointF getCenterPoint(SelDat d);

        DatType getDatType(SelDat item);

        void setHighLight(bool value);

        void setMapObject(MapObj* value);
        MapObj* getMapObj();

        void showConfig();


    protected:
        void setTypes(QVector<DatInfo> inputTypes, QVector<DatInfo> outputTypes);
        void setCaption(QString txt);

        QRectF vrect;
        enum { Type = UserType + 1 };
        QString caption;

        bool vSelected;

        struct PicPoint
        {
            DatInfo dtype;
            QPointF ul;
            QPointF br;
        };

        QVector<PicPoint> vInput;
        QVector<PicPoint> vOutput;

        bool isHighlighted;

        MapObj* filt;

};

#endif // VVIEW_H
