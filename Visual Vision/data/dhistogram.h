/*****************************************************************************
 * Copyright Tim Price
 *****************************************************************************/

#ifndef DHISTOGRAM_H
#define DHISTOGRAM_H

#include "general.h"
#include "data/data.h"

#include <QVector>


/*****************************************************************************
 * DATA
 * Histogram
 *****************************************************************************/
class DHistogram : public Data
{
    public:
        DHistogram();
        ~DHistogram();

        virtual DatType getType();

        void setData(QVector<int> val);
        QVector<int> getData();

        int getMaxValue();


    private:
        QVector<int> dat;
};

#endif // DHISTOGRAM_H
