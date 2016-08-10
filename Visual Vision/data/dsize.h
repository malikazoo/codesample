/*****************************************************************************
 * Copyright Tim Price
 *****************************************************************************/

#ifndef DSIZE_H
#define DSIZE_H

#include "general.h"
#include "data/data.h"



/*****************************************************************************
 * DATA
 * Size (Width, Height)
 *****************************************************************************/
class DSize : public Data
{
    public:
        DSize();
        virtual ~DSize();
        virtual DatType getType();

        QSize getSize();
        void setSize(QSize size);

    private:
        QSize vSize;

};

#endif // DSIZE_H
