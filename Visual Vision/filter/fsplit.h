/*****************************************************************************
 * Copyright Tim Price
 *****************************************************************************/

#ifndef FSPLIT_H
#define FSPLIT_H

#include "filter/filter.h"
#include "filterfactory.h"

#include "general.h"
#include "fsplitdialog.h"

#include <QDebug>

#include <vector>
using namespace std;

/*****************************************************************************
 * Filter
 * Splits a 3 channel image into 3 single channel images
 *****************************************************************************/
class FSplit : public Filter
{
    public:
        FSplit(QObject *parent = 0);
        ~FSplit();

        static QString getName();
        QString getCaption();

        virtual QVector<DatInfo> getInputTypes();
        virtual QVector<DatInfo> getOutputTypes();

        void showConfig();

    private:
        QMap<QString, QVariant> getData();
        void setData(QMap<QString, QVariant> data);
        FSplitDialog dialog;

        void reset();
        QVector<Data*> run(QVector<Data*> dat);

};

#endif // FSPLIT_H
