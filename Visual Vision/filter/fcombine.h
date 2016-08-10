/*****************************************************************************
 * Copyright Tim Price
 *****************************************************************************/

#ifndef FCOMBINE_H
#define FCOMBINE_H

#include "filter/filter.h"
#include "filterfactory.h"
#include "fcombinedialog.h"

#include "general.h"

#include <QDebug>

#include <vector>
using namespace std;


/*****************************************************************************
 * Combine
 *
 * Combines 3 single channel images into 1 3 channel image
 *
 * INPUTS: IMAGE1, IMAGE1, IMAGE1
 * OUTPUTS: IMAGE3
 * INHERITS FROM: Filter
 *****************************************************************************/
class FCombine : public Filter
{
    public:
        explicit FCombine(QObject *parent = 0);
        ~FCombine();

        static QString getName();
        QString getCaption();

        virtual QVector<DatInfo> getInputTypes();
        virtual QVector<DatInfo> getOutputTypes();

        void showConfig();

    protected:
        QMap<QString, QVariant> getData();
        void setData(QMap<QString, QVariant> data);
        FCombineDialog dialog;

        void reset();
        QVector<Data*> run(QVector<Data*> dat);
};

#endif // FCOMBINE_H
