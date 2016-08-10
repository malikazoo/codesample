/*****************************************************************************
 * Copyright Tim Price
 *****************************************************************************/

#ifndef FDRAWCIRCLE_H
#define FDRAWCIRCLE_H

#include <QVector>

#include "filterfactory.h"
#include "filter/filter.h"
#include "filter/fdrawcircledialog.h"

#include "data/data.h"
#include "data/dimage1.h"
#include "data/dimage3.h"

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
using namespace cv;

/*****************************************************************************
 * DrawCircle
 *
 * Draw given circles on an image
 *
 * INPUTS: IMAGE3, CIRCLES
 * OUTPUTS: IMAGE3
 * INHERITS FROM: Filter
 *****************************************************************************/
class FDrawCircle : public Filter
{
        Q_OBJECT
    public:
        explicit FDrawCircle(QObject *parent = 0);
        ~FDrawCircle();

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
        FDrawCircleDialog dialog;
        void reset();
        QVector<Data*> run(QVector<Data*> dat);
};

#endif // FDRAWCIRCLE_H
