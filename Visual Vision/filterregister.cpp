#include "filterregister.h"
#include "filterfactory.h"
#include "inputfactorybase.h"
#include "outputfactorybase.h"

FilterRegister* FilterRegister::instance = NULL;

/*****************************************************************************
 *
 *****************************************************************************/
FilterRegister::FilterRegister()
{

}

/*****************************************************************************
 * Returns the singleton instance of the filter registry
 *****************************************************************************/
FilterRegister* FilterRegister::getInstance()
{
    if (!instance)
    {
        instance = new FilterRegister();
    }

    return instance;
}

/*****************************************************************************
 * Add a filter to the registry
 *****************************************************************************/
void FilterRegister::Register(FilterFactoryBase *factory)
{
    filters.push_back(factory);
}

/*****************************************************************************
 * Returns a list of all the filters
 *****************************************************************************/
QVector<FilterFactoryBase*> FilterRegister::getFilters()
{
    return filters;
}

/*****************************************************************************
 * Returns a filter
 *****************************************************************************/
FilterFactoryBase* FilterRegister::getFilter(int id)
{
    return filters[id];
}

/*****************************************************************************
 *
 *****************************************************************************/
FilterFactoryBase* FilterRegister::getFilter(QString name)
{
    for (int i = 0; i < filters.size(); i++)
    {
        if (filters[i]->getName() == name)
            return filters[i];
    }

    return NULL;
}

/*****************************************************************************
 *
 *****************************************************************************/
void FilterRegister::RegisterInput(InputFactoryBase* factory)
{
    inputs.push_back(factory);
}

/*****************************************************************************
 *
 *****************************************************************************/
QVector<InputFactoryBase*> FilterRegister::getInputs()
{
    return inputs;
}

/*****************************************************************************
 *
 *****************************************************************************/
InputFactoryBase*FilterRegister::getInput(int id)
{
    return inputs[id];
}

/*****************************************************************************
 *
 *****************************************************************************/
InputFactoryBase* FilterRegister::getInput(QString name)
{
    for (int i = 0; i < inputs.size(); i++)
    {
        if (inputs[i]->getName() == name)
        {
            return inputs[i];
        }
    }

    return NULL;
}

/*****************************************************************************
 *
 *****************************************************************************/
void FilterRegister::RegisterOutput(OutputFactoryBase* factory)
{
    outputs.push_back(factory);
}

/*****************************************************************************
 *
 *****************************************************************************/
QVector<OutputFactoryBase*> FilterRegister::getOutputs()
{
    return outputs;
}

/*****************************************************************************
 *
 *****************************************************************************/
OutputFactoryBase* FilterRegister::getOutput(int id)
{
    return outputs[id];
}

/*****************************************************************************
 *
 *****************************************************************************/
OutputFactoryBase* FilterRegister::getOutput(QString name)
{
    for (int i = 0; i < outputs.size(); i++)
    {
        if (outputs[i]->getName() == name)
        {
            return outputs[i];
        }
    }

    return NULL;
}


