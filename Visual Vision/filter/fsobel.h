/*****************************************************************************
 * Copyright Tim Price
 *****************************************************************************/

#ifndef FSOBEL_H
#define FSOBEL_H

#include "filter/filter.h"
#include "filterfactory.h"

#include "filter/fsobeldialog.h"

#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

/*****************************************************************************
 * The Sobel Kernel
 *****************************************************************************/
class FSobel : public Filter
{
    public:
        FSobel(QObject *parent = 0);
        ~FSobel();

        static QString getName();
        QString getCaption();

        virtual QVector<DatInfo> getInputTypes();
        virtual QVector<DatInfo> getOutputTypes();


        void showConfig();

    private:
        QMap<QString, QVariant> getData();
        void setData(QMap<QString, QVariant> data);
        FSobelDialog dialog;
        int type;
        int ksize;

        void reset();
        QVector<Data*> run(QVector<Data*> dat);
};

#endif // FSOBEL_H
