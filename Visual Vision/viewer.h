/*****************************************************************************
 * Copyright Tim Price
 *****************************************************************************/

#ifndef VIEWER_H
#define VIEWER_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QList>
#include <QMouseEvent>
#include <QPointF>
#include "filter/filter.h"

#include "filtermap.h"
#include "viewscene.h"
#include "general.h"

/*****************************************************************************
 * Inherited from the QGraphicsView.  Provides a view to the canvas for the map
 *****************************************************************************/
class Viewer : public QGraphicsView
{
    Q_OBJECT
    public:
        explicit Viewer(QWidget *parent = 0);
        ~Viewer();
        void mouseMoveEvent(QMouseEvent *event);
        void mousePressEvent(QMouseEvent *event);
        void mouseReleaseEvent(QMouseEvent *event);
        void mouseDoubleClickEvent(QMouseEvent *event);

        void setfiltermap(FilterMap* fm);

        void reloadFilters();
        void clearScene();

        void addObject(QString name, QPointF location, int id, QMap<QString, QVariant> data);
        void addConnection(connectionOut itm);

        QList<VView*> getViews();


    protected:
        void keyPressEvent(QKeyEvent *event);

    signals:
        void updateWindow();

    public slots:
        void updateSystem();

    private:
        void deleteCurrent();
        ViewScene* scn;      

        ClickSel si;
        int siLine;

        QPointF selectedPos;
        FilterMap* map;


};

#endif // VIEWER_H
