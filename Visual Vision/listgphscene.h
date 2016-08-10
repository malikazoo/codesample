/*****************************************************************************
 * Copyright Tim Price
 *****************************************************************************/

#ifndef LISTGPHSCENE_H
#define LISTGPHSCENE_H

#include <QGraphicsScene>
#include <QListWidget>
#include <QDrag>
#include <QDragLeaveEvent>
#include <QMimeData>
#include <QGraphicsItem>
#include <QDebug>
#include <QVector>

#include "gphlistitem.h"
#include "listitem.h"

/*****************************************************************************
 *
 *****************************************************************************/
class ListGphScene : public QGraphicsScene
{
        Q_OBJECT
    public:
        explicit ListGphScene(QObject *parent = 0);

        void addGphItem(GphListItem item);


    signals:

    public slots:

    private:
        QVector<GphListItem> filterList;
        QVector<GphListItem> inputList;
        QVector<GphListItem> outputList;
        int currY;
        void rclear();
        void rredraw();

};

#endif // LISTGPHSCENE_H
