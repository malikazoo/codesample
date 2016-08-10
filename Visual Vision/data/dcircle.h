/*****************************************************************************
 * Copyright Tim Price
 *****************************************************************************/

#ifndef DCIRCLE_H
#define DCIRCLE_H

#include "general.h"
#include "data/data.h"

/*****************************************************************************
 *
 *****************************************************************************/
class DCircle : public Data
{
    public:
        DCircle();
        ~DCircle();

        virtual DatType getType();

        QVector<Circle> getData();
        void setData(QVector<Circle> dat);

    private:
        QVector<Circle> data;
};

#endif // DCIRCLE_H
