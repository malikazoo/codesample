/*****************************************************************************
 * Copyright Tim Price
 *****************************************************************************/

#ifndef DNONE_H
#define DNONE_H

#include "general.h"
#include "data/data.h"


/*****************************************************************************
 * DATA
 * Essentially holds a NULL
 *****************************************************************************/
class DNone : public Data
{
    public:
        DNone();
        ~DNone();

        DatType getType();

};

#endif // DNONE_H
