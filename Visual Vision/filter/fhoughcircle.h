/*****************************************************************************
 * Copyright Tim Price
 *****************************************************************************/

#ifndef FHOUGHCIRCLE_H
#define FHOUGHCIRCLE_H

#include "filterfactory.h"
#include "filter/filter.h"
#include "filter/fhoughcircledialog.h"

#include "general.h"
#include "data/dcircle.h"
#include "data/dimage1.h"

#include <vector>
using namespace std;
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

/*****************************************************************************
 * Hough Circle
 *
 * Finds Circles in an image using the Hough Circle Algorithm
 *
 * INPUTS: IMAGE1
 * OUTPUTS: CIRCLES
 * INHERITS FROM: Filter
 *****************************************************************************/
class FHoughCircle : public Filter
{
        Q_OBJECT
    public:
        explicit FHoughCircle(QObject *parent = 0);
        ~FHoughCircle();

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
        FHoughCircleDialog dialog;
        void reset();
        QVector<Data*> run(QVector<Data*> dat);
};

#endif // FHOUGHCIRCLE_H
