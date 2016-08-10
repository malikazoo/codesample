/*****************************************************************************
 * Copyright Tim Price
 *****************************************************************************/

#ifndef FTHRESHOLD_H
#define FTHRESHOLD_H

#include "filter/filter.h"
#include "filter/fthresholddialog.h"
#include "filterfactory.h"

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;

/*****************************************************************************
 *
 *****************************************************************************/
class FThreshold : public Filter
{
        Q_OBJECT
    public:
        explicit FThreshold(QObject *parent = 0);
        ~FThreshold();

        static QString getName();
        QString getCaption();

        virtual QVector<DatInfo> getInputTypes();
        virtual QVector<DatInfo> getOutputTypes();

        void showConfig();

    signals:

    public slots:

    private:
        QMap<QString, QVariant> getData();
        void setData(QMap<QString, QVariant> data);
        FThresholdDialog dialog;
        void reset();
        QVector<Data*> run(QVector<Data*> dat);

};

#endif // FTHRESHOLD_H
