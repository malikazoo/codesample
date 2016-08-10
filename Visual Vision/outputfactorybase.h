/*****************************************************************************
 * Copyright Tim Price
 *****************************************************************************/

#ifndef OUTPUTFACTORYBASE_H
#define OUTPUTFACTORYBASE_H

#include "output/output.h"

#include "filterregister.h"

/*****************************************************************************
 *
 *****************************************************************************/
class OutputFactoryBase
{
    public:
        OutputFactoryBase();

        virtual Output* CreateOutput() const = 0;

        virtual QString getName() = 0;
};


template <class T>
class OutputFactory : public OutputFactoryBase
{
    public:
        Output* CreateOutput() const
        {
            return new T;
        }

        virtual QString getName() { return T::getName(); }

};

#endif // OUTPUTFACTORYBASE_H
