#include "outputfactorybase.h"

/*****************************************************************************
 *
 *****************************************************************************/
OutputFactoryBase::OutputFactoryBase()
{
    FilterRegister* registry = FilterRegister::getInstance();
    registry->RegisterOutput(this);
}
