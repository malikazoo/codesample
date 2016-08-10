#include <iostream>
#include <sstream>
#include <string>
#include <QVector>
#include <QString>
using namespace std;

#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/calib3d/calib3d.hpp"
using namespace cv;

#include "videoreader.h"

int BOARDHEIGHT = 13;
int BOARDWIDTH = 2;
int CHECKER_SIZE = 1;




struct distortParam
{
    double rms;
    Mat cameraMatrix;
    Mat distortion;
};



vector<Point3f> buildObjectPoints(int width, int height, double checkersize)
{
    vector<Point3f> outpoints;
    for (int j = 0; j < height; j++)
    {
        for (int k = 0; k < width; k++)
        {
            outpoints.push_back(Point3f(k*checkersize,j*checkersize,0));
        }
    }

    return outpoints;
}

int main()
{

    Size boardSize(BOARDWIDTH,BOARDHEIGHT);
    Size imageSize(850,480);

    string nameEnd = ".png";

    int vid3c = 7785;
    int vid2c = 7683;
    int vid11c = 8419;
    int vid16c = 9424;


    distortParam dpl;
    distortParam dpr;

    videoreader read;
    read.readFile("videos.json");


    vector<vector<Point3f> > objectpoints;
    vector<vector<Point2f> > imagepointsl;
    vector<vector<Point2f> > imagepointsr;

    vector<Point2f> cornersr;
    vector<Point2f> cornersl;

    QVector<Mat> firstframe = read.firstframe();

    imwrite("f1.png",firstframe[0]);
    imwrite("f2.png",firstframe[1]);
    imwrite("f3.png",firstframe[2]);
    imwrite("f4.png",firstframe[3]);




/*
    for (int i = 0; i < firstframe.size(); i++)
    {
        imwrite(QString("image" + QString::number(i)+".png").toStdString().c_str(),firstframe[i]);
    }
*/

    cornersl.push_back(Point2f(667.9,351));
    cornersl.push_back(Point2f(639.6,359.9));
    cornersl.push_back(Point2f(611.0,369.4));
    cornersl.push_back(Point2f(581.8,379.0));
    cornersl.push_back(Point2f(552,388));
    cornersl.push_back(Point2f(521.0,397.9));
    cornersl.push_back(Point2f(490,408));
    cornersl.push_back(Point2f(458,418));
    cornersl.push_back(Point2f(425.5,429.2));
    cornersl.push_back(Point2f(392.8,440));
    cornersl.push_back(Point2f(358.8,450.2));
    cornersl.push_back(Point2f(325.2,461));
    cornersl.push_back(Point2f(289.5,472.5));

    cornersl.push_back(Point2f(652.8,323.5));
    cornersl.push_back(Point2f(625.0,331.2));
    cornersl.push_back(Point2f(596.8,340.2));
    cornersl.push_back(Point2f(568.8,349.5));
    cornersl.push_back(Point2f(539,358));
    cornersl.push_back(Point2f(509.5,367.8));
    cornersl.push_back(Point2f(479.0,377.0));
    cornersl.push_back(Point2f(448.2,386.5));
    cornersl.push_back(Point2f(416.5,396.2));
    cornersl.push_back(Point2f(384.2,406.8));
    cornersl.push_back(Point2f(351.5,416.8));
    cornersl.push_back(Point2f(318.2,427));
    cornersl.push_back(Point2f(283.8,437));




    cornersr.push_back(Point2f(620.8, 454.5));
    cornersr.push_back(Point2f(577.0,443.2));
    cornersr.push_back(Point2f(536,432));
    cornersr.push_back(Point2f(495.8,421));
    cornersr.push_back(Point2f(457.2,410.5));
    cornersr.push_back(Point2f(419.8,401));
    cornersr.push_back(Point2f(383.5,392));
    cornersr.push_back(Point2f(348.5,382.2));
    cornersr.push_back(Point2f(315.2,373.5));
    cornersr.push_back(Point2f(282.2,365));
    cornersr.push_back(Point2f(250.2,356.2));
    cornersr.push_back(Point2f(219.8,348.2));
    cornersr.push_back(Point2f(189.5,341.2));

    cornersr.push_back(Point2f(622.2,421.0));
    cornersr.push_back(Point2f(582.2,411.0));
    cornersr.push_back(Point2f(542.8,401));
    cornersr.push_back(Point2f(505.0,391.8));
    cornersr.push_back(Point2f(468.2,383.2));
    cornersr.push_back(Point2f(433.2,373.8));
    cornersr.push_back(Point2f(398.0,365.2));
    cornersr.push_back(Point2f(365.5,356.8));
    cornersr.push_back(Point2f(332.5,349.2));
    cornersr.push_back(Point2f(301.5,341.2));
    cornersr.push_back(Point2f(271.0,333.8));
    cornersr.push_back(Point2f(241.5,325.8));
    cornersr.push_back(Point2f(212.8,318.8));


    Mat picl = imread("image0.png",CV_LOAD_IMAGE_COLOR);
    Mat picr = imread("image1.png",CV_LOAD_IMAGE_COLOR);
    Mat bwpicl;
    cvtColor(picl,bwpicl,CV_BGR2GRAY);
    Mat bwpicr;
    cvtColor(picr,bwpicr,CV_BGR2GRAY);

    //objectpoints.push_back(buildObjectPoints(BOARDWIDTH,BOARDHEIGHT,CHECKER_SIZE));

    //cornerSubPix (bwpicl, cornersl, boardSize, cvSize (-1, -1), cvTermCriteria (TermCriteria::COUNT + TermCriteria::EPS, 30, 1e-6));
    //cornerSubPix (bwpicr, cornersr, boardSize, cvSize (-1, -1), cvTermCriteria (TermCriteria::COUNT + TermCriteria::EPS, 30, 1e-6));
    imagepointsl.push_back(cornersl);
    imagepointsr.push_back(cornersr);

    drawChessboardCorners(picl,boardSize,cornersl,true);
    drawChessboardCorners(picr,boardSize,cornersr,true);
    imshow("LeftImage",picl);
    imshow("RightImage",picr);
    cvWaitKey();

    objectpoints.push_back(buildObjectPoints(BOARDWIDTH,BOARDHEIGHT,CHECKER_SIZE));

    Mat rotation;
    Mat translation;
    Mat essential;
    Mat fundamental;

    Mat dplmat = read.getCamMatrix(0);
    Mat dprmat = read.getCamMatrix(1);
    Mat dpldist = read.getDistortion(0);
    Mat dprdist = read.getDistortion(1);

    stereoCalibrate(objectpoints,imagepointsl,imagepointsr,dplmat,dpldist,
                    dprmat,dprdist,imageSize,rotation,translation,essential,fundamental,
                    cvTermCriteria(TermCriteria::COUNT | TermCriteria::EPS, 30, 1e-6), CV_CALIB_FIX_INTRINSIC | CV_CALIB_SAME_FOCAL_LENGTH | CV_CALIB_ZERO_TANGENT_DIST);


    cout << "rotation: " << rotation << endl;
    cout << "translation: " << translation << endl;
    cout << "essential: " << essential << endl;
    cout << "fundamental: " << fundamental << endl;

    cvWaitKey();

    /*
    imshow("Leftimage",picl);
    imshow("Rightimage",picr);

    Mat bwpicl;
    cvtColor(picl,bwpicl,CV_BGR2GRAY);
    Mat bwpicr;
    cvtColor(picr,bwpicr,CV_BGR2GRAY);

    cvWaitKey();

    //for (int i = 0 ; i < 32; i++)
    /*
    {

        //Left Image
        {
            findChessboardCorners(picr, boardSize, cornersl, CV_CALIB_CB_ADAPTIVE_THRESH + CV_CALIB_CB_NORMALIZE_IMAGE);
            cornerSubPix (picr, cornersl, boardSize, cvSize (-1, -1), cvTermCriteria (TermCriteria::COUNT + TermCriteria::EPS, 30, 1e-6));
            drawChessboardCorners(picl,boardSize,cornersl,true);
            imagepointsl.push_back(cornersl);
            imshow("LeftImage",picl);
        }

        namedWindow("LeftImage", CV_WINDOW_AUTOSIZE);
        namedWindow("RightImage", CV_WINDOW_AUTOSIZE);
        //Right Image
        {
            findChessboardCorners(picr, boardSize, cornersr, CV_CALIB_CB_ADAPTIVE_THRESH + CV_CALIB_CB_NORMALIZE_IMAGE);
            cornerSubPix (picr, cornersr, boardSize, cvSize (-1, -1), cvTermCriteria (TermCriteria::COUNT + TermCriteria::EPS, 30, 1e-6));
            drawChessboardCorners(picr,boardSize,cornersr,true);
            imagepointsr.push_back(cornersr);
            imshow("RightImage",picr);
        }

        waitKey();

        objectpoints.push_back(buildObjectPoints(BOARDWIDTH,BOARDHEIGHT,CHECKER_SIZE));

    }

    cout << endl;


    Mat rotation;
    Mat translation;
    Mat essential;
    Mat fundamental;


    stereoCalibrate(objectpoints,imagepointsl,imagepointsr,dpl.cameraMatrix,dpl.distortion,
                    dpr.cameraMatrix,dpr.distortion,imageSize,rotation,translation,essential,fundamental,
                    cvTermCriteria(TermCriteria::COUNT | TermCriteria::EPS, 30, 1e-6), CV_CALIB_FIX_INTRINSIC | CV_CALIB_SAME_FOCAL_LENGTH | CV_CALIB_ZERO_TANGENT_DIST);


    cout << "rotation: " << rotation << endl;
    cout << "translation: " << translation << endl;
    cout << "essential: " << essential << endl;
    cout << "fundamental: " << fundamental << endl;

    FileStorage outfile("stereoparams.yml", FileStorage::WRITE);
    outfile << "rotation" << rotation;
    outfile << "translation" << translation;
    outfile << "essential" << essential;
    outfile << "fundamental" << fundamental;

*/
    return 0;
}

