/*****************************************************************************
 * Copyright Tim Price
 *****************************************************************************/

#ifndef DREAL_H
#define DREAL_H

#include "general.h"
#include "data/data.h"


class DReal : public Data
{
    public:
        DReal();
        virtual ~DReal();
        virtual DatType getType();

        double getValue();
        void setValue(double val);

    private:
        double vVal;
};

#endif // DREAL_H
