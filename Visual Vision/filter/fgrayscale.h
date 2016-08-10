/*****************************************************************************
 * Copyright Tim Price
 *****************************************************************************/

#ifndef FGRAYSCALE_H
#define FGRAYSCALE_H

#include "filter/filter.h"
#include "filterfactory.h"
#include "fcombinedialog.h"

#include "data/data.h"
#include "data/dimage3.h"

#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

/*****************************************************************************
 * Color to Grayscale
 *
 * Converts Color image to Grayscale image
 *
 * INPUTS: IMAGE3
 * OUTPUTS: IMAGE1
 * INHERITS FROM: Filter
 *****************************************************************************/
class FGrayscale : public Filter
{
    public:
        FGrayscale(QObject *parent = 0);
        ~FGrayscale();

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



#endif // FGRAYSCALE_H
