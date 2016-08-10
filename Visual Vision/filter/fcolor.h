/*****************************************************************************
 * Copyright Tim Price
 *****************************************************************************/

#ifndef FCOLOR_H
#define FCOLOR_H

#include "filter.h"
#include "filterfactory.h"

#include "fcolordialog.h"

#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;


/*****************************************************************************
 * Grayscale to Color
 *
 * Converts Grayscale image to Color image
 *
 * INPUTS: IMAGE1
 * OUTPUTS: IMAGE3
 * INHERITS FROM: Filter
 *****************************************************************************/
class FColor : public Filter
{
    public:
        explicit FColor(QObject *parent = 0);
        ~FColor();

        static QString getName();
        QString getCaption();

        virtual QVector<DatInfo> getInputTypes();
        virtual QVector<DatInfo> getOutputTypes();

        void showConfig();

    protected:
        QMap<QString, QVariant> getData();
        void setData(QMap<QString, QVariant> data);
        void reset();
        QVector<Data*> run(QVector<Data*> dat);

        FColorDialog dialog;

};

#endif // FCOLOR_H
