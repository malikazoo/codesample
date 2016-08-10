#ifndef VIDEOREADER_H
#define VIDEOREADER_H

#include <iostream>
#include <QString>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>
#include <QVector>
using namespace std;

#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/calib3d/calib3d.hpp"
using namespace cv;

/*****************************************************************************
 * The structure that holds information for the video files.  Used by the
 * object to load the videos
 *****************************************************************************/
struct videoinfo
{
    int id;
    QString location;
    int firstframe;
    double rms;
    Mat cammatrix;
    Mat distortion;
};

/*****************************************************************************
 * Stores all of the videos information and returns the 4 videos synchronized
 *****************************************************************************/
class videoreader
{
    public:
        videoreader();
        void readFile(QString location);

        QVector<Mat> firstframe();
        QVector<Mat> nextframe();

        int getWidth();
        int getHeight();

        Mat getCamMatrix(int id);
        Mat getDistortion(int id);




   private:
        videoinfo vidinfo[4];

        VideoCapture vid[4];    //OpenCV Video files that read in and decode the images
        bool isopen;            //Video files are open
        int width;              //Maximum Width of all videos
        int height;             //Maximum Height of all videos
};

#endif // VIDEOREADER_H
