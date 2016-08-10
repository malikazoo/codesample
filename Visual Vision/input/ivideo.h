/*****************************************************************************
 * Copyright Tim Price
 *****************************************************************************/

#ifndef IVIDEO_H
#define IVIDEO_H

#include <QWidget>
#include <QDialog>
#include <QDebug>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;

#include "input/input.h"
#include "inputfactorybase.h"

#include "data/dimage3.h"
#include "data/dnone.h"

#include "vview.h"
#include "filebrowser.h"
#include "ivideoconfig.h"


/*****************************************************************************
 * INPUT
 * Provides a video to the system.  Provides successive images
 *****************************************************************************/
class IVideo : public Input
{
    public:
        IVideo(QObject *parent = 0);
        ~IVideo();

        virtual int getNumFrames();

        virtual QVector<Data*> getNextFrame();

        static QString getName();
        QString getCaption();

        virtual QVector<DatInfo> getOutputTypes();
        virtual QVector<Data*> getCurrentFrame();
        virtual void setFrameNum(int framenum);





        void showConfig();

    protected:
        virtual void reset();
        QMap<QString, QVariant> getData();
        void setData(QMap<QString, QVariant> data);


    private:
        IVideoConfig config;
        QString file;
        void reloadVideo();
        VideoCapture vid;
        int currLocation;
        bool vidOpen;

};

#endif // IVIDEO_H
