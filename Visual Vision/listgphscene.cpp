#include "listgphscene.h"

/*****************************************************************************
 *
 *****************************************************************************/
ListGphScene::ListGphScene(QObject *parent) :
    QGraphicsScene(parent)
{
    //this->setDragDropMode(QAbstractItemView::DragOnly);
    currY = 0;
}

/*****************************************************************************
 *
 *****************************************************************************/
void ListGphScene::addGphItem(GphListItem item)
{
    if (item.getType() == FILTER)
    {
        filterList.push_back(item);
    }
    else if (item.getType() == INPUT)
    {
        inputList.push_back(item);
    }
    else //OUTPUT
    {
        outputList.push_back(item);
    }

    rredraw();
}

/*****************************************************************************
 * Clear the list, removing all the objects and deleting them
 *****************************************************************************/
void ListGphScene::rclear()
{
    QList<QGraphicsItem*> im = this->items();
    for (QList<QGraphicsItem*>::iterator i = im.begin(); i != im.end(); i++)
    {
        QGraphicsItem* r = *i;
        this->removeItem(r);
        delete r;
    }

    this->clear();
    currY = 0;
}

/*****************************************************************************
 * Gets the needed information from the list and redraw
 *****************************************************************************/
void ListGphScene::rredraw()
{
    rclear();

    //Input objects
    ListItem* h1 = new ListItem();
    h1->setAsTitle(true);
    h1->setText("INPUTS");
    h1->setPosY(currY);
    h1->setData(32, QVariant(-1));
    h1->setData(33, QVariant(-1));
    currY += 17;
    this->addItem(h1);

    for (int i = 0; i < inputList.size(); i++)
    {
        GphListItem item = inputList[i];
        ListItem* txt = new ListItem();
        txt->setText(item.getText());
        txt->setPosY(currY);
        txt->setData(32, QVariant(item.getId()));
        txt->setData(33, QVariant(item.getType()));
        this->addItem(txt);
        currY += 17;
    }

    //Output objects
    ListItem* h2 = new ListItem();
    h2->setAsTitle(true);
    h2->setText("OUTPUTS");
    h2->setPosY(currY);
    h2->setData(32, QVariant(-1));
    h2->setData(33, QVariant(-1));
    currY += 17;
    this->addItem(h2);

    for (int i = 0; i < outputList.size(); i++)
    {
        GphListItem item = outputList[i];
        ListItem* txt = new ListItem();
        txt->setText(item.getText());
        txt->setPosY(currY);
        txt->setData(32, QVariant(item.getId()));
        txt->setData(33, QVariant(item.getType()));
        this->addItem(txt);
        currY += 17;
    }

    //Filter objects
    ListItem* h3 = new ListItem();
    h3->setAsTitle(true);
    h3->setText("FILTERS");
    h3->setPos(0,currY);
    h3->setData(32, QVariant(-1));
    h3->setData(33, QVariant(-1));
    currY += 17;
    this->addItem(h3);

    for (int i = 0; i < filterList.size(); i++)
    {
        GphListItem item = filterList[i];
        ListItem* txt = new ListItem();
        txt->setText(item.getText());
        txt->setPosY(currY);
        txt->setData(32, QVariant(item.getId()));
        txt->setData(33, QVariant(item.getType()));
        this->addItem(txt);
        currY += 17;
    }

}

