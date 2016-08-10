/*****************************************************************************
 * Copyright Tim Price
 *****************************************************************************/

#ifndef FHOUGHLINES_H
#define FHOUGHLINES_H

#include "filter/filter.h"
#include "filterfactory.h"
#include "fhoughlinedialog.h"

#include "data/data.h"
#include "data/dimage1.h"
#include "data/dline.h"

#include <vector>
using namespace std;

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

/*****************************************************************************
 *
 *****************************************************************************/
class FHoughLines : public Filter
{
        Q_OBJECT
    public:
        explicit FHoughLines(QObject *parent = 0);
        ~FHoughLines();

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
        FHoughLineDialog dialog;
        void reset();
        QVector<Data*> run(QVector<Data*> dat);

};

#endif // FHOUGHLINES_H
