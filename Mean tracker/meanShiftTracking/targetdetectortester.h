#ifndef TARGETDETECTORTESTER_H
#define TARGETDETECTORTESTER_H

#include "targetdetector.h"

class TargetDetectorTester
{
public:
    TargetDetectorTester();
    ~TargetDetectorTester();

    void testTargetDetection(const string & pReferenceImgFile, Rect referenceRect, const string & pTargetImgFile);

    void testObjectDetection();


private:
    TargetDetector * mpTargetDetector;

    Mat  mReferenceImg;
    Rect mReferenceRect;
    Mat  mTargetImg;
    Rect mTargetRect;

};

#endif // TARGETDETECTORTESTER_H
