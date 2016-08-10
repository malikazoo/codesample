/*****************************************************************************
 * Copyright Tim Price
 *****************************************************************************/

#ifndef INPUTFACTORYBASE_H
#define INPUTFACTORYBASE_H

#include <QString>

#include "input/input.h"

#include "filterregister.h"

/*****************************************************************************
 * Creates input objects
 *****************************************************************************/
class InputFactoryBase
{
    public:
        InputFactoryBase();

        virtual Input* CreateInput() const = 0;

        virtual QString getName() = 0;
};


template <class T>
class InputFactory : public InputFactoryBase
{
    public:
        Input* CreateInput() const
        {
            return new T;
        }

        virtual QString getName() { return T::getName(); }

};


#endif // INPUTFACTORYBASE_H
