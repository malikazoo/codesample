/*****************************************************************************
 * Copyright Tim Price
 *****************************************************************************/

#ifndef DLINE_H
#define DLINE_H

#include "general.h"
#include "data/data.h"


#include <QVector>
#include <QPointF>
#include <QLineF>


/*****************************************************************************
 * DATA
 * Line (2 points)
 *****************************************************************************/
class DLine : public Data
{
    public:
        DLine();
        ~DLine();

        DatType getType();

        QVector<QLineF> getLines();
        void setLines(QVector<QLineF> v);



    private:
        QVector<QLineF> lin;
};


#endif // DLINE_H
