#ifndef OCAMERA_H
#define OCAMERA_H


#include "output.h"
#include "data/data.h"
#include "data/dimage1.h"
#include "oscreenconfig.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;

/*****************************************************************************
 * Camera
 *****************************************************************************/
class OCamera : public Output
{
    public:
        OCamera();

        static QString getName();
        QString getCaption();

        virtual QVector<DatType> getInputTypes();

        void showConfig();

    private:
        void reset();
        QVector<Data*> run(QVector<Data*> dat);
};

#endif // OCAMERA_H
