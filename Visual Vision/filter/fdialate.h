/*****************************************************************************
 * Copyright Tim Price
 *****************************************************************************/

#ifndef FDIALATE_H
#define FDIALATE_H

#include <QObject>

#include "filterfactory.h"
#include "filter/filter.h"
#include "filter/fdialatedialog.h"

#include "data/data.h"
#include "data/dimage1.h"

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;


/*****************************************************************************
 * Dilate
 *
 * Dialates an image
 *
 * INPUTS: IMAGE1
 * OUTPUTS: IMAGE1
 * INHERITS FROM: Filter
 *****************************************************************************/
class FDialate : public Filter
{
    public:
        explicit FDialate(QObject *parent = 0);
        ~FDialate();

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
        FDialateDialog dialog;
        void reset();
        QVector<Data*> run(QVector<Data*> dat);


};

#endif // FDIALATE_H
