/*****************************************************************************
 * Copyright Tim Price
 *****************************************************************************/

#ifndef FILTERFACTORY_H
#define FILTERFACTORY_H

#include "filter/filter.h"

class FilterRegister;

/*****************************************************************************
 * Filter Factory will create new filters on demand.
 *****************************************************************************/
class FilterFactoryBase
{
    public:
        FilterFactoryBase();
        virtual Filter* CreateFilter() const = 0;

        virtual QString getName() = 0;

    private:

};

template <class T>
class FilterFactory : public FilterFactoryBase
{
    public:
        Filter* CreateFilter() const
        {
            return new T;
        }

        virtual QString getName() { return T::getName(); }

};


#endif // FILTERFACTORY_H
