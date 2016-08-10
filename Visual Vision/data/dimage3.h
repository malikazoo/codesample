/*****************************************************************************
 * Copyright Tim Price
 *****************************************************************************/

#ifndef DIMAGE3_H
#define DIMAGE3_H

#include "general.h"
#include "data/data.h"

#include <opencv2/core/core.hpp>
using namespace cv;


/*****************************************************************************
 * DATA
 * Color Image
 *****************************************************************************/
class DImage3 : public Data
{
    public:
        DImage3();
        ~DImage3();
        DatType getType();

        void setImage(Mat img);
        Mat getImage();


    private:
        Mat image;
};

#endif // DIMAGE3_H
