/*****************************************************************************
 * Copyright Tim Price
 *****************************************************************************/

#ifndef FRESIZE_H
#define FRESIZE_H

#include "filter.h"
#include "filterfactory.h"
#include "filter/fresizedialog.h"
#include <QVector>

#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

/*****************************************************************************
 *
 *****************************************************************************/
class FResize : public Filter
{
        Q_OBJECT
    public:
        explicit FResize(QObject *parent = 0);
        ~FResize();


        static QString getName();
        QString getCaption();

        virtual QVector<DatInfo> getInputTypes();
        virtual QVector<DatInfo> getOutputTypes();


        void showConfig();

    private:
        QMap<QString, QVariant> getData();
        void setData(QMap<QString, QVariant> data);
        FResizeDialog dialog;
        void reset();
        QVector<Data*> run(QVector<Data*> dat);

    signals:

    public slots:

};

#endif // FRESIZE_H
