/*****************************************************************************
 * Copyright Tim Price
 *****************************************************************************/

#ifndef IIMAGE_H
#define IIMAGE_H

#include "input/input.h"
#include "inputfactorybase.h"

#include "iimageconfig.h"

#include "data/data.h"
#include "data/dimage3.h"

#include <QJsonObject>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;

/*****************************************************************************
 *
 *****************************************************************************/
class IImage : public Input
{
    public:
        IImage(QObject *parent = 0);

        virtual int getNumFrames();

        virtual QVector<Data*> getNextFrame();

        static QString getName();
        QString getCaption();

        virtual QVector<DatInfo> getOutputTypes();
        virtual QVector<Data*> getCurrentFrame();
        void setFrameNum(int framenum);

        void showConfig();

    protected:
        void reset();
        QMap<QString, QVariant> getData();
        void setData(QMap<QString, QVariant> data);


    private:
        IImageConfig config;
        QString file;
        void reloadImage();
        bool isloaded;
        Mat img;
};

#endif // IIMAGE_H
