#include "listgph.h"

/*****************************************************************************
 *
 *****************************************************************************/
ListGph::ListGph(QWidget *parent) :
    QGraphicsView(parent)
{
    scn = new ListGphScene(this);
    //this->setDragMode();
    this->setScene(scn);

    scn->setSceneRect(0,0,180,1000);
}

/*****************************************************************************
 *
 *****************************************************************************/
ListGph::~ListGph()
{

}

/*****************************************************************************
 *
 *****************************************************************************/
void ListGph::addItem(GphListItem item)
{
    scn->addGphItem(item);
}

/*****************************************************************************
 * Starts a drag and drop.
 *****************************************************************************/
void ListGph::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);

    QList<QGraphicsItem*> ite = scn->items();
    for(QList<QGraphicsItem*>::iterator it = ite.begin(); it != ite.end(); it++)
    {
        QGraphicsItem* i = *it;
        if (i->isUnderMouse())
        {
            QMimeData* mimeData = new QMimeData();
            QByteArray ba;
            ba = QByteArray::number(i->data(32).toInt());
            QByteArray bb;
            bb = QByteArray::number(i->data(33).toInt());
            mimeData->setData("application/x-filter", ba);
            mimeData->setData("application/x-type", bb);
            QDrag* drag = new QDrag(this);
            drag->setMimeData(mimeData);
            drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction);
        }
    }

}

/*****************************************************************************
 *
 *****************************************************************************/
void ListGph::redraw()
{

}

