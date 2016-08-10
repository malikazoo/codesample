/*****************************************************************************
 * Copyright Tim Price
 *****************************************************************************/

#ifndef FCANNY_H
#define FCANNY_H

#include "filter/filter.h"
#include "filterfactory.h"
#include "filter/fcannydialog.h"

#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;


/*****************************************************************************
 * Canny Edges
 *
 * Allows user to find edges using the Canny algorithm
 *
 * INPUTS: IMAGE1
 * OUTPUTS: IMAGE1
 * INHERITS FROM: Filter
 *****************************************************************************/
class FCanny : public Filter
{
        Q_OBJECT
    public:
        explicit FCanny(QObject *parent = 0);
        ~FCanny();

        static QString getName();
        QString getCaption();

        virtual QVector<DatInfo> getInputTypes();
        virtual QVector<DatInfo> getOutputTypes();

        void showConfig();

    protected:
        QMap<QString, QVariant> getData();
        void setData(QMap<QString, QVariant> data);
        FCannyDialog dialog;
        void reset();
        QVector<Data*> run(QVector<Data*> dat);

    signals:

    public slots:

};

#endif // FCANNY_H
