#include "targetdetectortester.h"
#include <qdebug.h>

TargetDetectorTester::TargetDetectorTester()
{
    mpTargetDetector = new TargetDetector();
}

TargetDetectorTester::~TargetDetectorTester()
{
   if(mpTargetDetector)
   {
       delete mpTargetDetector;
       mpTargetDetector = NULL;
   }
}

void TargetDetectorTester::testObjectDetection()
{

}




void TargetDetectorTester::testTargetDetection(const string & pReferenceImgFile, Rect referenceRect, const string & pTargetImgFile)
{
#ifdef WIN32
    IplImage* ref_img = cvLoadImage(pReferenceImgFile.c_str());
    mReferenceImg = Mat(ref_img);
#else
    mReferenceImg = imread(pReferenceImgFile, CV_LOAD_IMAGE_COLOR);
#endif
    if(mReferenceImg.data==NULL)
    {
        qDebug() << "Loading reference image: " << QString::fromStdString(pReferenceImgFile) << " failed";
        return;
    }
#ifdef WIN32
    IplImage* targ_img = cvLoadImage(pReferenceImgFile.c_str());
    mTargetImg = Mat(targ_img);
#else
    mTargetImg = imread(pTargetImgFile, CV_LOAD_IMAGE_COLOR);
#endif
    if(mTargetImg.data==NULL)
    {
        qDebug() << "Loading target image: " << QString::fromStdString(pTargetImgFile) << " failed";
        return;
    }
    mReferenceRect = referenceRect;

    mTargetRect = mpTargetDetector->findTarget(mReferenceImg, mReferenceRect, mTargetImg);

    qDebug() << "Detect Object in Rect ";
    qDebug() << "X: " << mTargetRect.x << " Y: " << mTargetRect.y << " W: " << mTargetRect.width << " H: " << mTargetRect.height;


    rectangle(mReferenceImg, mReferenceRect, cvScalar(255,0,0));
    namedWindow( "Reference window", WINDOW_AUTOSIZE );
    imshow( "Reference window", mReferenceImg );

    waitKey(0);

    rectangle(mTargetImg, mTargetRect, cvScalar(255,0,0));
    namedWindow( "Target window", WINDOW_AUTOSIZE );
    imshow( "Target window", mTargetImg );

    waitKey(0);

#ifdef WIN32
    if(ref_img)
    {
        delete ref_img;
        ref_img = NULL;
    }
    if(targ_img)
    {
        delete targ_img;
        targ_img = NULL;
    }
#endif
}
