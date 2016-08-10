/*****************************************************************************
 * Copyright Tim Price
 *****************************************************************************/

#ifndef DLIST_H
#define DLIST_H

#include "general.h"
#include "data/data.h"

#include <QVector>


/*****************************************************************************
 *
 *****************************************************************************/
class DList : public Data
{
    public:
        DList();
        ~DList();

         DatType getType();

         QVector<double> getData();
         void setData(QVector<double> val);

    private:
         QVector<double> dat;
};

#endif // DLIST_H
