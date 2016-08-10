#include "viewer.h"

/*****************************************************************************
 *
 *****************************************************************************/
Viewer::Viewer(QWidget *parent) :
    QGraphicsView(parent)
{
    scn = new ViewScene(this);

    this->setScene(scn);

    scn->setSceneRect(0,0,1000, 1000);

    si.itemClicked = NULL;
    si.clickType = ClickSel::C_NONE;

    connect(scn,SIGNAL(updateSystem()),this,SLOT(updateSystem()));

    this->setMouseTracking(false);
}

/*****************************************************************************
 *
 *****************************************************************************/
Viewer::~Viewer()
{
    //clear();
}

/*****************************************************************************
 * If the user is selecting a MapObj input or output, then move the line that
 * is connected.  If selecting a MapObj object then move it
 *****************************************************************************/
void Viewer::mouseMoveEvent(QMouseEvent *event)
{
    QPointF pt = this->mapToScene(event->pos());
    if (si.itemClicked != NULL && event->buttons() == Qt::LeftButton)
    {
        if (si.clickType == ClickSel::C_NONE)
        {
            si.itemClicked->setPos(pt - selectedPos);
            scn->itemMoved(si);
        }
        else
        {
            scn->moveLineDraw(pt);
        }
    }
}

/*****************************************************************************
 * If the user is clicking on a MapObj input or output, start a line draw.
 * If the user is clicking on a MapObj, then select it
 *****************************************************************************/
void Viewer::mousePressEvent(QMouseEvent *event)
{
    QPointF pt = this->mapToScene(event->pos());

    ClickSel f = scn->getMouseOver(pt);

    if (f.itemClicked == NULL)
    {
        si.itemClicked = NULL;
        siLine = scn->getConnectionOver(pt);
        scn->highlightLine(siLine);

        scn->clearHighLight();
    }
    else
    {
        scn->highlightLine(0);

        if (f.clickType == ClickSel::C_NONE)
        {
            si = f;
            selectedPos = pt - si.itemClicked->pos();
            scn->highlightView(f);
        }
        else
        {
            si = f;
            scn->beginLineDraw(f);
            scn->clearHighLight();
        }
    }

    scn->update();
}

/*****************************************************************************
 * User has released the mouse button.  If the user was drawing a line, end
 * the line drawing.
 *****************************************************************************/
void Viewer::mouseReleaseEvent(QMouseEvent *event)
{
    QPointF pt = this->mapToScene(event->pos());
    ClickSel f = scn->getMouseOver(pt);
    if (si.itemClicked != NULL)
    {
        if (si.clickType == ClickSel::C_NONE)
        {
            selectedPos.setX(0);
            selectedPos.setY(0);
            scn->removeCurrLine();
        }
        else
        {
            scn->endLineDraw(f);
        }
    }
}

/*****************************************************************************
 * User has double clicked on the viewer.  Send the signal to the scene
 *****************************************************************************/
void Viewer::mouseDoubleClickEvent(QMouseEvent *event)
{
    scn->mouseDoubleClick(event->pos());
}

/*****************************************************************************
 *
 *****************************************************************************/
void Viewer::setfiltermap(FilterMap* fm)
{
    map = fm;
}

/*****************************************************************************
 *
 *****************************************************************************/
void Viewer::clearScene()
{
    scn->cleanAll();
}

/*****************************************************************************
 *
 *****************************************************************************/
void Viewer::addObject(QString name, QPointF location, int id, QMap<QString, QVariant> data)
{
    scn->addObject(name,location,id,data);
}

/*****************************************************************************
 *
 *****************************************************************************/
void Viewer::addConnection(connectionOut itm)
{
    scn->addConnection(itm);
}

/*****************************************************************************
 *
 *****************************************************************************/
QList<VView*> Viewer::getViews()
{
    return scn->getViews();
}

/*****************************************************************************
 * User has pressed a key on the viewer
 * Delete - remove the selected MapObj or connection
 *****************************************************************************/
void Viewer::keyPressEvent(QKeyEvent* event)
{
    switch(event->key())
    {
        case Qt::Key_Delete:
            deleteCurrent();
        break;
    }
}

/*****************************************************************************
 * Update the program to reflect any changes
 *****************************************************************************/
void Viewer::updateSystem()
{
    map->updateSystem();
    emit updateWindow();
}

/*****************************************************************************
 *  Delete the current selected MapObj or connection
 *****************************************************************************/
void Viewer::deleteCurrent()
{
    if (si.itemClicked != NULL)
        scn->deleteView(si.itemClicked);
    else if (siLine > 0)
        scn->deleteConnection(siLine);
}
