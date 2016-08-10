#include "inputfactorybase.h"

/*****************************************************************************
 *
 *****************************************************************************/
InputFactoryBase::InputFactoryBase()
{
    FilterRegister* registry = FilterRegister::getInstance();
    registry->RegisterInput(this);
}
