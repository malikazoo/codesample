#ifndef MEANSHIFTFILTER_H
#define MEANSHIFTFILTER_H

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include <vector>

using namespace cv;

class MeanShiftFilter
{
public:
    MeanShiftFilter();

    IplImage * filter(const IplImage* img, int iterationNum=100);

    int mSpatialRadius;
    int mRangeRadius;
    double mShiftDelta;

private:
    vector<float> readImgLuv(const IplImage* img, int i, int j);
    bool writeImgLuv(const IplImage* img, int i, int j, vector<float> luv);


};

#endif // MEANSHIFTFILTER_H
