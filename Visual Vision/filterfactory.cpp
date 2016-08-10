#include "filterfactory.h"
#include "filterregister.h"

/*****************************************************************************
 *
 *****************************************************************************/
FilterFactoryBase::FilterFactoryBase()
{
    FilterRegister* registry = FilterRegister::getInstance();
    registry->Register(this);
}
