/*****************************************************************************
 * Copyright Tim Price
 *****************************************************************************/

#ifndef FHISTOGRAM_H
#define FHISTOGRAM_H

#include "filter/filter.h"
#include "filterfactory.h"

/*****************************************************************************
 * Histogram
 *
 * Generates a Histogram from an imput image
 *
 * INPUTS: IMAGE1
 * OUTPUTS: HISTOGRAM
 * INHERITS FROM: Filter
 *****************************************************************************/
class FHistogram : public Filter
{
        Q_OBJECT
    public:
        explicit FHistogram(QObject *parent = 0);
        ~FHistogram();

        static QString getName();
        QString getCaption();

        virtual QVector<DatInfo> getInputTypes();
        virtual QVector<DatInfo> getOutputTypes();

        void showConfig();


    signals:

    public slots:

    protected:
        QMap<QString, QVariant> getData();
        void setData(QMap<QString, QVariant> data);
        void reset();
        QVector<Data*> run(QVector<Data*> dat);

};

#endif // FHISTOGRAM_H
