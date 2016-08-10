/*****************************************************************************
 * Copyright Tim Price
 *****************************************************************************/

#ifndef FLAPLACIAN_H
#define FLAPLACIAN_H

#include "filter/filter.h"
#include "filterfactory.h"
#include "filter/flaplaciandialog.h"

#include "data/data.h"
#include "data/dimage1.h"

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;

/*****************************************************************************
 *
 *****************************************************************************/
class FLaplacian : public Filter
{
        Q_OBJECT
    public:
        explicit FLaplacian(QObject *parent = 0);
        ~FLaplacian();

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
        FLaplacianDialog dialog;
        void reset();
        QVector<Data*> run(QVector<Data*> dat);


};

#endif // FLAPLACIAN_H
