#include "viewscene.h"

/*****************************************************************************
 *
 *****************************************************************************/
ViewScene::ViewScene(QObject *parent) :
    QGraphicsScene(parent)
{
    registry = FilterRegister::getInstance();
    map = FilterMap::getInstance();
    currLine = NULL;
}

/*****************************************************************************
 * User has dropped a new MapObj onto the screen
 *****************************************************************************/
void ViewScene::dropEvent(QGraphicsSceneDragDropEvent* event)
{
    QByteArray itemdata = event->mimeData()->data("application/x-filter");
    QByteArray itemtype = event->mimeData()->data("application/x-type");

    int itemid = itemdata.toInt();
    int itype = itemtype.toInt();

    if (itype >= 0)
    {
        if (itype == INPUT)
        {
            //Create the dropped input, add it to the map and the viewer
            InputFactoryBase* filt = registry->getInput(itemid);
            Input* f = filt->CreateInput();
            map->addInput(f);
            VView* v = new VView();
            v->setPos(event->scenePos());
            v->setMapObject(f);
            views.push_back(v);
            this->addItem(v);
        }
        else if (itype == OUTPUT)
        {
            //Create the dropped output, add it to the map and the viewer
            OutputFactoryBase* filt = registry->getOutput(itemid);
            Output* f = filt->CreateOutput();
            map->addOutput(f);
            VView* v = new VView();
            v->setPos(event->scenePos());
            v->setMapObject(f);
            views.push_back(v);
            this->addItem(v);
        }
        else
        {
            //Create the dropped filter, add it to the map and the viewer
            FilterFactoryBase* filt = registry->getFilter(itemid);
            Filter* f = filt->CreateFilter();
            map->addFilter(f);
            VView* v = new VView();
            v->setPos(event->scenePos());
            v->setMapObject(f);
            views.push_back(v);
            this->addItem(v);
        }
    }
}

/*****************************************************************************
 *
 *****************************************************************************/
void ViewScene::dragEnterEvent(QGraphicsSceneDragDropEvent* event)
{
    event->accept();
}

/*****************************************************************************
 *
 *****************************************************************************/
void ViewScene::dragMoveEvent(QGraphicsSceneDragDropEvent* event)
{
    event->accept();
}

/*****************************************************************************
 * Deletes the current line from the scene in the case that the line being
 * drawn does not comply with the rules set for creating a line
 *****************************************************************************/
void ViewScene::removeCurrLine()
{
    if (currLine != NULL)
    {
        this->removeItem(currLine);
        delete currLine;
        currLine = NULL;
    }
}

/*****************************************************************************
 * Show the config dialog box for a view and then update the viewer to reflect
 * any changes
 *****************************************************************************/
void ViewScene::mouseDoubleClick(QPointF pos)
{
    ClickSel pnt = getMouseOver(pos);

    if (pnt.itemClicked != NULL)
    {
        pnt.itemClicked->showConfig();
        emit updateSystem();
    }
}

/*****************************************************************************
 *
 *****************************************************************************/
QList<VView*> ViewScene::getViews()
{
    return views;
}

/*****************************************************************************
 *
 *****************************************************************************/
void ViewScene::cleanAll()
{
    for (QList<VView*>::iterator it = views.begin(); it != views.end(); it++)
    {
        deleteView(*it);
    }
}

/*****************************************************************************
 * Used when loading in file.  Creates an object in the current location with
 * the current id
 *****************************************************************************/
void ViewScene::addObject(QString name, QPointF location, int id, QMap<QString, QVariant> data)
{
    FilterFactoryBase* filt = registry->getFilter(name);
    if (filt != NULL)
    {
        Filter* f = filt->CreateFilter();
        f->setId(id);
        f->setRep(data);
        map->addFilter(f);
        VView* v = new VView();
        v->setPos(location);
        v->setMapObject(f);
        views.push_back(v);
        this->addItem(v);
        return;
    }

    InputFactoryBase* input = registry->getInput(name);
    if (input != NULL)
    {
        Input* i = input->CreateInput();
        i->setId(id);
        i->setRep(data);
        map->addInput(i);
        VView* v = new VView();
        v->setPos(location);
        v->setMapObject(i);
        views.push_back(v);
        this->addItem(v);
        return;
    }

    OutputFactoryBase* output = registry->getOutput(name);
    if (output != NULL)
    {
        Output* o = output->CreateOutput();
        o->setId(id);
        o->setRep(data);
        map->addOutput(o);
        VView* v = new VView();
        v->setPos(location);
        v->setMapObject(o);
        views.push_back(v);
        this->addItem(v);
        return;
    }

}

void ViewScene::addConnection(connectionOut conn)
{
    conn.id1;
    conn.item1;
    conn.type1;

    ClickSel dat1;
    ClickSel dat2;

    dat1.itemClicked = NULL;
    dat2.itemClicked = NULL;

    for (int i = 0; i < views.size(); i++)
    {
        VView* v = views[i];
        int mapid = v->getMapObj()->getId();
        if (mapid == conn.id1)
        {
            dat1.itemClicked = v;
        }
        else if (mapid == conn.id2)
        {
            dat2.itemClicked = v;
        }
    }

    if (conn.type1 == 0)
    {
        dat1.clickType = ClickSel::C_IN;
    }
    else if (conn.type1 == 1)
    {
        dat1.clickType = ClickSel::C_OUT;
    }
    else
    {
        dat1.clickType = ClickSel::C_NONE;
    }

    if (conn.type2 == 0)
    {
        dat2.clickType = ClickSel::C_IN;
    }
    else if (conn.type2 == 1)
    {
        dat2.clickType = ClickSel::C_OUT;
    }
    else
    {
        dat2.clickType = ClickSel::C_NONE;
    }

    dat1.num = conn.item1;
    dat2.num = conn.item2;

    if (conn.type1 == 0)
    {
        SelDat d1;
        d1.selected = SelDat::C_IN;
        d1.itemnum = conn.item1;

        SelDat d2;
        d2.selected = SelDat::C_OUT;
        d2.itemnum = conn.item2;

        QPointF n = dat1.itemClicked->getCenterPoint(d1);
        QPointF m = dat2.itemClicked->getCenterPoint(d2);

        if (currLine == NULL)
            currLine = new QGraphicsLineItem();

        currLine->setLine(m.x()+ dat2.itemClicked->pos().x(), m.y() + dat2.itemClicked->pos().y(), n.x()+dat1.itemClicked->pos().x(), n.y() + dat1.itemClicked->pos().y());
        this->addItem(currLine);
        int conn = map->createConnection(dat2,dat1);
        if (conn != 0)
        {
            LinePP p;
            p.lineItem = currLine;
            p.pt1 = dat2;
            p.pt2 = dat1;
            lines[conn] = p;
            currLine = NULL;
            return;
        }
    }
    else if (conn.type1 == 1)
    {
        SelDat d1;
        d1.selected = SelDat::C_OUT;
        d1.itemnum = conn.item1;

        SelDat d2;
        d2.selected = SelDat::C_IN;
        d2.itemnum = conn.item2;

        QPointF n = dat1.itemClicked->getCenterPoint(d1);
        QPointF m = dat2.itemClicked->getCenterPoint(d2);

        if (currLine == NULL)
            currLine = new QGraphicsLineItem();

        currLine->setLine(n.x()+dat1.itemClicked->pos().x(), n.y() + dat1.itemClicked->pos().y(), m.x()+ dat2.itemClicked->pos().x(), m.y() + dat2.itemClicked->pos().y());
        this->addItem(currLine);
        int conn = map->createConnection(dat1,dat2);
        if (conn != 0)
        {
            LinePP p;
            p.lineItem = currLine;
            p.pt1 = dat1;
            p.pt2 = dat2;
            lines[conn] = p;
            currLine = NULL;
            return;
        }
    }
}

/*****************************************************************************
 * Determines the center location of a given piece
 *****************************************************************************/
QPointF ViewScene::calcLocation(ClickSel item)
{
    VView* r = item.itemClicked;
    SelDat dat;
    if (item.clickType == ClickSel::C_IN)
        dat.selected = SelDat::C_IN;
    else if (item.clickType == ClickSel::C_OUT)
        dat.selected = SelDat::C_OUT;
    else
        dat.selected = SelDat::C_NONE;
    dat.itemnum = item.num;

    QPointF n = r->getCenterPoint(dat);
    return n;
}

/*****************************************************************************
 * The user has begun to draw a line
 *****************************************************************************/
void ViewScene::beginLineDraw(ClickSel s)
{
    lineBegin = s;

    VView* r = s.itemClicked;
    QPointF n = calcLocation(s);

    currLine = new QGraphicsLineItem();
    QLine lineN;
    lineN.setP1(QPoint(n.x() + r->pos().x(), n.y() + r->pos().y()));
    lineN.setP2(QPoint(n.x() + r->pos().x(), n.y() + r->pos().y()));
    currLine->setLine(lineN);
    this->addItem(currLine);
}

/*****************************************************************************
 * The user is drawing a line, therefore, the beginnning of the line remains
 * fixed and the end of the line follows the cursor
 *****************************************************************************/
void ViewScene::moveLineDraw(QPointF s)
{
    if (currLine == NULL)
        return;

    currLine->setLine(currLine->line().x1(), currLine->line().y1(), s.x(), s.y());
}

/*****************************************************************************
 * The user has ended the line draw and is attempting to connect one filter
 * to another.  Run preliminary tests to see if it is a valid connection.  If
 * it passes the preliminary tests, then attempt to create the connection
 * with the map object.  If the map returns a non 0 number, then a valid
 * connection and that number becomes the id of the connection
 *****************************************************************************/
void ViewScene::endLineDraw(ClickSel s)
{
    if (s.itemClicked != NULL)
    {
        //Line was drawn forward
        if (s.clickType == ClickSel::C_IN && lineBegin.clickType == ClickSel::C_OUT)
        {
            VView* r = s.itemClicked;
            SelDat dat;
            dat.selected = SelDat::C_IN;
            dat.itemnum = s.num;

            QPointF n = r->getCenterPoint(dat);
            currLine->setLine(currLine->line().x1(), currLine->line().y1(), n.x()+r->pos().x(), n.y() + r->pos().y());

            //Once run through preliminary tests, then attempt to add to map. If successful,
            //then keep.  If not successful, then delete
            int conn = map->createConnection(lineBegin, s);
            if (conn != 0)
            {
                LinePP p;
                p.lineItem = currLine;
                p.pt1 = lineBegin;
                p.pt2 = s;
                lines[conn] = p;
                currLine = NULL;
                return;
            }
        }
        //Line was drawn backwards
        else if (s.clickType == ClickSel::C_OUT && lineBegin.clickType == ClickSel::C_IN)
        {
            VView* r = s.itemClicked;
            SelDat dat;
            dat.selected = SelDat::C_OUT;
            dat.itemnum = s.num;

            QPointF n = r->getCenterPoint(dat);
            currLine->setLine(n.x()+r->pos().x(), n.y() + r->pos().y(), currLine->line().x1(), currLine->line().y1());

            //Once run through preliminary tests, then attempt to add to map. If successful,
            //then keep.  If not successful, then delete
            int conn = map->createConnection(s, lineBegin);
            if (conn != 0)
            {
                LinePP p;
                p.lineItem = currLine;
                p.pt1 = s;
                p.pt2 = lineBegin;
                lines[conn] = p;
                currLine = NULL;
                return;
            }
        }
    }

    removeCurrLine();
}

/*****************************************************************************
 * A filter has been moved.  Update the lines that connect to the filter
 * to make them follow the filter
 *****************************************************************************/
void ViewScene::itemMoved(ClickSel item)
{
    for (QMap<int, LinePP>::iterator it = lines.begin(); it != lines.end(); it++)
    {
        LinePP pp = *it;
        if (pp.pt1.itemClicked == item.itemClicked)
        {
            //Move assocated line to reflect movement of object
            VView* r = item.itemClicked;
            SelDat dat;
            if (pp.pt1.clickType == ClickSel::C_IN)
                dat.selected = SelDat::C_IN;
            else if (pp.pt1.clickType == ClickSel::C_OUT)
                dat.selected = SelDat::C_OUT;
            else
                dat.selected = SelDat::C_NONE;
            dat.itemnum = pp.pt1.num;

            QPointF n = r->getCenterPoint(dat);
            pp.lineItem->setLine(n.x() + r->pos().x(), n.y() + r->pos().y(), pp.lineItem->line().x2(), pp.lineItem->line().y2());
        }
        if (pp.pt2.itemClicked == item.itemClicked)
        {
            //Move assocated line to reflect movement of object
            VView* r = item.itemClicked;
            SelDat dat;
            if (pp.pt2.clickType == ClickSel::C_IN)
                dat.selected = SelDat::C_IN;
            else if (pp.pt2.clickType == ClickSel::C_OUT)
                dat.selected = SelDat::C_OUT;
            else
                dat.selected = SelDat::C_NONE;
            dat.itemnum = pp.pt2.num;

            QPointF n = r->getCenterPoint(dat);
            pp.lineItem->setLine(pp.lineItem->line().x1(), pp.lineItem->line().y1(), n.x() + r->pos().x(), n.y() + r->pos().y());
        }
    }
}

/*****************************************************************************
 * Determines which connection line the mouse is over
 *****************************************************************************/
int ViewScene::getConnectionOver(QPointF pos)
{
    const double selFuzz = 3;

    for (QMap<int, LinePP>::iterator it = lines.begin(); it != lines.end(); it++)
    {
        int i = it.key();
        LinePP s = it.value();
        QLineF l = s.lineItem->line();

        double px = 0;
        double py = 0;
        double qx = 0;
        double qy = 0;

        if (l.x1() <= l.x2())
        {
            px = l.x1();
            py = l.y1();
            qx = l.x2();
            qy = l.y2();
        }
        else
        {
            qx = l.x1();
            qy = l.y1();
            px = l.x2();
            py = l.y2();
        }

        double rx = pos.x();
        double ry = pos.y();

        if (rx + selFuzz < px || qx < rx - selFuzz)
            continue;
        else if (ry + selFuzz < qMin(py, qy) || qMax(py,qy) < ry - selFuzz)
        {
            continue;
        }

        double dx = qx - px;
        double dy = qy - py;

        if (dx == 0 || dy == 0)
            return i;

        double slope = dy / dx;
        double offset = py - px * slope;
        double calculatedY = rx * slope + offset;

        if (ry - selFuzz <= calculatedY && calculatedY <= ry + selFuzz)
            return i;

    }
    return 0;
}

/*****************************************************************************
 * Highlights the given line
 *****************************************************************************/
void ViewScene::highlightLine(int id)
{
    for (QMap<int, LinePP>::iterator it = lines.begin(); it != lines.end(); it++)
    {
        int i = it.key();
        LinePP s = it.value();
        if (i == id)
        {
            s.lineItem->setPen(QPen(QColor(Qt::blue)));
        }
        else
            s.lineItem->setPen(QPen(QColor(Qt::black)));
    }
}

/*****************************************************************************
 * Removes the given connection
 *****************************************************************************/
void ViewScene::deleteConnection(int id)
{
    if (lines.contains(id))
    {
        this->removeItem(lines[id].lineItem);
        delete lines[id].lineItem;
        lines.remove(id);
    }

    map->deleteConnection(id);
}

/*****************************************************************************
 * Deletes the given view
 *****************************************************************************/
void ViewScene::deleteView(VView* itm)
{
    QVector<int> toerase;

    for (QMap<int, LinePP>::iterator it = lines.begin(); it != lines.end(); it++)
    {
        LinePP value = it.value();
        if (value.pt1.itemClicked == itm || value.pt2.itemClicked == itm)
        {
            toerase.push_back(it.key());
        }
    }

    for (int i = 0; i < toerase.size(); i++)
    {
        deleteConnection(toerase[i]);
    }

    MapObj* obj = itm->getMapObj();

    views.removeAll(itm);
    this->removeItem(itm);
    map->deleteView(obj);

    delete itm;

}

/*****************************************************************************
 * Returns which view if any are under the mouse
 *****************************************************************************/
ClickSel ViewScene::getMouseOver(QPointF pt)
{
    ClickSel ans;

    for (int i = 0; i < views.size(); i++)
    {
        VView* item = views[i];

        if (item->isUnderMouse())
        {
            ans.itemClicked = item;
            ans.clickType = ClickSel::C_NONE;
            QPointF r = pt - item->pos();
            SelDat d = item->getClicked(r);
            if (d.selected == SelDat::C_NONE)
                ans.clickType = ClickSel::C_NONE;
            else if (d.selected == SelDat::C_IN)
                ans.clickType = ClickSel::C_IN;
            else
                ans.clickType = ClickSel::C_OUT;
            ans.num = d.itemnum;
        }
    }

    return ans;
}

/*****************************************************************************
 * Highlight the given view
 *****************************************************************************/
void ViewScene::highlightView(ClickSel view)
{
    for (int i = 0; i < views.size(); i++)
    {
        VView* v = views[i];
        if (v == view.itemClicked)
            v->setHighLight(true);
        else
            v->setHighLight(false);
    }
}

/*****************************************************************************
 * Clears the highlighting of VView
 *****************************************************************************/
void ViewScene::clearHighLight()
{
    for (int i = 0; i < views.size(); i++)
    {
        VView* v = views[i];
        v->setHighLight(false);
    }

}
