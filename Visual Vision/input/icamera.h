/*****************************************************************************
 * Copyright Tim Price
 *****************************************************************************/

#ifndef ICAMERA_H
#define ICAMERA_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;

#include "input/input.h"
#include "inputfactorybase.h"

#include "data/dimage3.h"
#include "data/dnone.h"

#include "vview.h"
#include "filebrowser.h"
#include "icameradialog.h"

/*****************************************************************************
 *
 *****************************************************************************/
class ICamera : public Input
{
    public:
        ICamera();

        virtual int getNumFrames();

        virtual QVector<Data*> getNextFrame();

        static QString getName();
        QString getCaption();

        virtual QVector<DatInfo> getOutputTypes();
        virtual QVector<Data*> getCurrentFrame();
        virtual void setFrameNum(int);

        void showConfig();

    protected:
        void setData(QMap<QString, QVariant> data);
        virtual void reset();
        QMap<QString, QVariant> getData();

    private:
        ICameraDialog config;
        QString file;
        void reloadVideo();
        VideoCapture vid;
        int currLocation;
        bool vidOpen;
};

#endif // ICAMERA_H
