/*****************************************************************************
 * Copyright Tim Price
 *****************************************************************************/

#ifndef FERODE_H
#define FERODE_H

#include <QObject>

#include "filterfactory.h"
#include "filter/filter.h"
#include "filter/ferodedialog.h"

#include "data/data.h"
#include "data/dimage1.h"

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;


/*****************************************************************************
 * Erode
 *
 * Erodes an image
 *
 * INPUTS: IMAGE1
 * OUTPUTS: IMAGE1
 * INHERITS FROM: Filter
 *****************************************************************************/
class FErode : public Filter
{
        Q_OBJECT
    public:
        FErode(QObject *parent = 0);
        ~FErode();

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
        FErodeDialog dialog;
        void reset();
        QVector<Data*> run(QVector<Data*> dat);

};

#endif // FERODE_H
