/*****************************************************************************
 * Copyright Tim Price
 *****************************************************************************/

#ifndef FDISPLAYHISTOGRAM_H
#define FDISPLAYHISTOGRAM_H

#include "filter/filter.h"
#include "filterfactory.h"

#include <QVector>
#include "fdisplayhistogramdialog.h"


/*****************************************************************************
 * Display Histogram
 *
 * Takes a histogram and generates an image from it
 *
 * INPUTS: HISTOGRAM
 * OUTPUS: IMAGE3
 * INHERITS FROM: FILTER
 *****************************************************************************/
class FDisplayHistogram : public Filter
{
        Q_OBJECT
    public:
        explicit FDisplayHistogram(QObject *parent = 0);
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
        FDisplayHistogramDialog dialog;
        void reset();
        QVector<Data*> run(QVector<Data*> dat);

};

#endif // FDISPLAYHISTOGRAM_H
