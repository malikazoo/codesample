#include "dimage3.h"

/*****************************************************************************
 *
 *****************************************************************************/
DImage3::DImage3()
{
}

/*****************************************************************************
 *
 *****************************************************************************/
DImage3::~DImage3()
{

}

/*****************************************************************************
 * Full Color image
 *****************************************************************************/
DatType DImage3::getType()
{
    return IMAGE3;
}

/*****************************************************************************
 *
 *****************************************************************************/
void DImage3::setImage(Mat img)
{
    image = img;
}

/*****************************************************************************
 *
 *****************************************************************************/
Mat DImage3::getImage()
{
    return image;
}
