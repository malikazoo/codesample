/*****************************************************************************
 * Copyright Tim Price
 *****************************************************************************/

#ifndef LISTGPH_H
#define LISTGPH_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include "gphlistitem.h"
#include "listgphscene.h"

/*****************************************************************************
 * A List view that will be used to show the list of inputs, outputs and
 * filters
 *****************************************************************************/
class ListGph : public QGraphicsView
{
        Q_OBJECT
    public:
        explicit ListGph(QWidget *parent = 0);
        ~ListGph();

        void addItem(GphListItem item);

        void mousePressEvent(QMouseEvent *event);

        void redraw();


    signals:

    public slots:

    private:
        ListGphScene* scn;

};

#endif // LISTGPH_H
