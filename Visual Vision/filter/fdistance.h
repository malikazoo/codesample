/*****************************************************************************
 * Copyright Tim Price
 *****************************************************************************/

#ifndef FDISTANCE_H
#define FDISTANCE_H

#include "filter/filter.h"
#include "filterfactory.h"
#include "fdistancedialog.h"

#include <opencv2/core/core.hpp>

using namespace cv;

/*****************************************************************************
 * Distance
 *
 * Calculates the distance between the values of the image using either
 * Euclidean, Manhattan or Chebushev distance algorithms
 *
 * INPUTS: IMAGE1, IMAGE1
 * OUTPUTS: IMAGE1
 * INHERITS FROM: Filter
 *****************************************************************************/
class FDistance : public Filter
{
        Q_OBJECT
    public:
        explicit FDistance(QObject *parent = 0);
        ~FDistance();

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
        FDistanceDialog dialog;
        void reset();
        QVector<Data*> run(QVector<Data*> dat);
        

};

#endif // FDISTANCE_H
