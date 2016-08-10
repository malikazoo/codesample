/*****************************************************************************
 * Copyright Tim Price
 *****************************************************************************/

#ifndef IMAGE1_H
#define IMAGE1_H

#include "general.h"
#include "data/data.h"

#include <opencv2/core/core.hpp>
using namespace cv;


/*****************************************************************************
 * DATA
 * Grayscale Image
 *****************************************************************************/
class DImage1 : public Data
{
    public:
        DImage1();
        ~DImage1();
        DatType getType();

        void setImage(Mat img);
        Mat getImage();


    private:
        Mat image;
};

#endif // IMAGE1_H
