/*****************************************************************************
 * Copyright Tim Price
 *****************************************************************************/

#ifndef DPOINT_H
#define DPOINT_H

#include "general.h"
#include "data/data.h"

#include <QPointF>
#include <QVector>



/*****************************************************************************
 * DATA
 * A point
 *****************************************************************************/
class DPoint : public Data
{
    public:
        DPoint();
        ~DPoint();

        DatType getType();

        QVector<QPointF> getPoints();
        void setPoints(QVector<QPointF> ans);


    private:
        QVector<QPointF> points;
};

#endif // DPOINT_H
