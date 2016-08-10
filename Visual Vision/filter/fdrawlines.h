/*****************************************************************************
 * Copyright Tim Price
 *****************************************************************************/

#ifndef FDRAWLINES_H
#define FDRAWLINES_H

#include "filter/filter.h"
#include "filterfactory.h"
#include "fdrawlinesdialog.h"

#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

/*****************************************************************************
 * DrawLines
 *
 * Draws given lines onto an image
 *
 * INPUTS: IMAGE3, LINES
 * OUTPUTS: IMAGE3
 * INHERITS FROM: Filter
 *****************************************************************************/
class FDrawLines : public Filter
{
        Q_OBJECT
    public:
        explicit FDrawLines(QObject *parent = 0);
        ~FDrawLines();

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
        FDrawLinesDialog dialog;
        void reset();
        QVector<Data*> run(QVector<Data*> dat);
};

#endif // FDRAWLINES_H
