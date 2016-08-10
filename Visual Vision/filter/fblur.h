/*****************************************************************************
 * Copyright Tim Price
 *****************************************************************************/

#ifndef FBLUR_H
#define FBLUR_H

#include "filter/filter.h"
#include "filter/fblurdialog.h"
#include "filterfactory.h"

#include "data/data.h"
#include "data/dimage1.h"

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;


/*****************************************************************************
 * Blur
 *
 * Allows a user to blur an image in one of three ways
 *
 * INPUTS: IMAGE1
 * OUTPUTS: IMAGE1
 * INHERITED FROM: Filter
 *****************************************************************************/
class FBlur : public Filter
{
        Q_OBJECT

    public:
        explicit FBlur(QObject *parent = 0);
        ~FBlur();

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
        FBlurDialog dialog;
        void reset();
        QVector<Data*> run(QVector<Data*> dat);

};

#endif // FBLUR_H
