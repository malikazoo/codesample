/*****************************************************************************
 * Copyright Tim Price
 *****************************************************************************/

#ifndef FGOODFEATURESTOTRACK_H
#define FGOODFEATURESTOTRACK_H

#include "filter.h"
#include "filterfactory.h"
#include "fgoodfeaturestotrackdialog.h"

#include <QPointF>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

#include <vector>
using namespace std;

class FGoodFeaturesToTrack : public Filter
{
        Q_OBJECT
    public:
        explicit FGoodFeaturesToTrack(QObject *parent = 0);

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
        FGoodFeaturesToTrackDialog dialog;
        void reset();
        QVector<Data*> run(QVector<Data*> dat);
};

#endif // FGOODFEATURESTOTRACK_H
