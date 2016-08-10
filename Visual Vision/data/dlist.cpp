#include "dlist.h"

/*****************************************************************************
 *
 *****************************************************************************/
DList::DList()
{
}

/*****************************************************************************
 *
 *****************************************************************************/
DList::~DList()
{

}

/*****************************************************************************
 *
 *****************************************************************************/
DatType DList::getType()
{
    return LIST;
}

/*****************************************************************************
 *
 *****************************************************************************/
QVector<double> DList::getData()
{
    return dat;
}

/*****************************************************************************
 *
 *****************************************************************************/
void DList::setData(QVector<double> val)
{
    dat = val;
}