/*****************************************************************************
 * Copyright Tim Price
 *****************************************************************************/

#ifndef VIEWSCENE_H
#define VIEWSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneDragDropEvent>
#include <QDebug>
#include <QMimeData>

#include <QtGlobal>

#include "filterregister.h"
#include "filter/filter.h"
#include "input/input.h"
#include "output/output.h"
#include "filterfactory.h"
#include "inputfactorybase.h"
#include "outputfactorybase.h"
#include "filtermap.h"

/*****************************************************************************
 * Provides the actual canvas to the map.
 *****************************************************************************/
class ViewScene : public QGraphicsScene
{
    Q_OBJECT

    public:
        explicit ViewScene(QObject *parent = 0);

        void beginLineDraw(ClickSel s);
        void moveLineDraw(QPointF s);
        void endLineDraw(ClickSel s);

        void itemMoved(ClickSel item);

        int getConnectionOver(QPointF pos);
        void highlightLine(int id);

        void deleteConnection(int id);

        void deleteView(VView* itm);

        ClickSel getMouseOver(QPointF pt);
        void highlightView(ClickSel view);
        void clearHighLight();
        void removeCurrLine();
        void mouseDoubleClick(QPointF pos);

        QList<VView*> getViews();

        void cleanAll();

        void addObject(QString name, QPointF location, int id, QMap<QString, QVariant> data);
        void addConnection(connectionOut conn);


    protected:
        void dropEvent(QGraphicsSceneDragDropEvent *event);
        void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
        void dragMoveEvent(QGraphicsSceneDragDropEvent *event);


    signals:
        void updateSystem();

    public slots:

    private:
        FilterRegister* registry;
        FilterMap* map;

        struct LinePP //A line
        {
            LinePP(){lineItem = NULL;}
            QGraphicsLineItem* lineItem;
            ClickSel pt1;
            ClickSel pt2;
        };

        QMap<int, LinePP> lines;
        QList<VView*> views;

        bool linedrawing;
        QGraphicsLineItem* currLine;
        ClickSel lineBegin;

        QPointF calcLocation(ClickSel item);

};

#endif // VIEWSCENE_H
