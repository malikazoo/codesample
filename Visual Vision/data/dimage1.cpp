#include "dimage1.h"

/*****************************************************************************
 *
 *****************************************************************************/
DImage1::DImage1()
{
}

/*****************************************************************************
 *
 *****************************************************************************/
DImage1::~DImage1()
{

}

/*****************************************************************************
 * Grayscale image
 *****************************************************************************/
DatType DImage1::getType()
{
    return IMAGE1;
}

/*****************************************************************************
 *
 *****************************************************************************/
void DImage1::setImage(Mat img)
{
    image = img;
}

/*****************************************************************************
 *
 *****************************************************************************/
Mat DImage1::getImage()
{
    return image;
}

