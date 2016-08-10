/*****************************************************************************
 * Copyright Tim Price
 *****************************************************************************/

#ifndef GPHLISTITEM_H
#define GPHLISTITEM_H

#include <QString>
#include "general.h"


/*****************************************************************************
 * Holds an item placed in the list
 *****************************************************************************/
class GphListItem
{
    public:
        GphListItem();
        void setText(QString txt);
        void setId(int id);
        void setType(ListType lt);

        QString getText();
        int getId();
        ListType getType();

    private:
        QString vtext;
        int vid;
        ListType type;

};

#endif // GPHLISTITEM_H
