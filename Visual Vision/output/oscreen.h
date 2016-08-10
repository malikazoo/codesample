/*****************************************************************************
 * Copyright Tim Price
 *****************************************************************************/

#ifndef OSCREEN_H
#define OSCREEN_H

#include "output/output.h"
#include "outputfactorybase.h"

#include "data/data.h"
#include "data/dimage1.h"
#include "data/dimage3.h"
#include "oscreenconfig.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;

/*****************************************************************************
 * OUTPUT
 * Outputs the video to the screen
 *****************************************************************************/
class OScreen : public Output
{
    public:
        OScreen(QObject *parent = 0);

        static QString getName();
        QString getCaption();

        virtual QVector<DatInfo> getInputTypes();

        void showConfig();

    protected:
        QMap<QString, QVariant> getData();
        void setData(QMap<QString, QVariant> data);
        void reset();
        QVector<Data*> run(QVector<Data*> dat);


    private:
        OScreenConfig config;
        static int winNumber;
        QString currNumber;
};



#endif // OSCREEN_H
