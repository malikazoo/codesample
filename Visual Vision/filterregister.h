/*****************************************************************************
 * Copyright Tim Price
 *****************************************************************************/

#ifndef FILTERREGISTER_H
#define FILTERREGISTER_H

#include <QVector>

class FilterFactoryBase;
class InputFactoryBase;
class OutputFactoryBase;

/*****************************************************************************
 * Part of this code was derived from the technique used by
 * James E. Beveridge ("Self-Registering Objects in C++" in Dr. Dobbs Journal,
 * Copyright 1997)
 * Jim Beveridge
 * Email: jimb@empire.net
 *
 * Changes include using a singleton instance of the registry instead of
 * defining in main
 *
 * Stores the registry, a list of all possible filters, inputs and outputs
 *****************************************************************************/

class FilterRegister
{
    public:
        static FilterRegister* getInstance();

        void Register(FilterFactoryBase* factory);

        QVector<FilterFactoryBase*> getFilters();
        FilterFactoryBase* getFilter(int id);
        FilterFactoryBase* getFilter(QString name);

        void RegisterInput(InputFactoryBase* factory);
        QVector<InputFactoryBase*> getInputs();
        InputFactoryBase* getInput(int id);
        InputFactoryBase* getInput(QString name);

        void RegisterOutput(OutputFactoryBase* factory);
        QVector<OutputFactoryBase*> getOutputs();
        OutputFactoryBase* getOutput(int id);
        OutputFactoryBase* getOutput(QString name);


    private:
        FilterRegister();
        QVector<FilterFactoryBase*> filters;
        QVector<InputFactoryBase*> inputs;
        QVector<OutputFactoryBase*> outputs;

        static FilterRegister* instance;
};

#endif // FILTERREGISTER_H
