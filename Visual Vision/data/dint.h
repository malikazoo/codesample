/*****************************************************************************
 * Copyright Tim Price
 *****************************************************************************/

#ifndef DINT_H
#define DINT_H

#include "general.h"
#include "data/data.h"

/*****************************************************************************
 *
 *****************************************************************************/
class DInt : public Data
{
    public:
        DInt();
        virtual ~DInt();
        virtual DatType getType();


    private:
        int dat;
};

#endif // DINT_H
