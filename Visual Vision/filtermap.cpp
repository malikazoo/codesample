#include "filtermap.h"

FilterMap* FilterMap::instance = NULL;

/*****************************************************************************
 * Constructor
 *****************************************************************************/
FilterMap::FilterMap(QObject *parent) :
    QObject(parent)
{
    connId = 0;
    maxFrames = 0;
    currFrame = 0;
}

/*****************************************************************************
 *
 *****************************************************************************/
void FilterMap::setupForNextFrame()
{
    for (QList<Input*>::iterator i = inputs.begin(); i != inputs.end(); i++)
    {
        Input* f = *i;
        f->setupNextFrame();
    }

    for (QList<Output*>::iterator i = outputs.begin(); i != outputs.end(); i++)
    {
        Output* f = *i;
        f->setupNextFrame();
    }

    for (QList<Filter*>::iterator i = filters.begin(); i != filters.end(); i++)
    {
        Filter* f = *i;
        f->setupNextFrame();
    }

}

/*****************************************************************************
 * Returns the instance.  Singleton class
 *****************************************************************************/
FilterMap* FilterMap::getInstance()
{
    if (!instance)
    {
        instance = new FilterMap();
    }

    return instance;
}

/*****************************************************************************
 * Removes all items from the map.
 *****************************************************************************/
FilterMap::~FilterMap()
{
    for (QList<Filter*>::iterator it = filters.begin(); it != filters.end(); it++)
    {
        Filter* f = *it;
        delete f;
    }

    for (QList<Input*>::iterator it = inputs.begin(); it != inputs.end(); it++)
    {
        Input* f = *it;
        delete f;
    }

    for (QList<Output*>::iterator it = outputs.begin(); it != outputs.end(); it++)
    {
        Output* f = *it;
        delete f;
    }

}

/*****************************************************************************
 * Adds a filter to the map
 *****************************************************************************/
void FilterMap::addFilter(Filter* filt)
{
    filters.push_back(filt);
    updateSystem();
}

/*****************************************************************************
 * Adds an output to the map
 *****************************************************************************/
void FilterMap::addOutput(Output* filt)
{
    outputs.push_back(filt);
    updateSystem();
}

/*****************************************************************************
 * Adds an input to the map
 *****************************************************************************/
void FilterMap::addInput(Input* filt)
{
    inputs.push_back(filt);
    updateSystem();
}

/*****************************************************************************
 * Creates a new connection
 *****************************************************************************/
int FilterMap::createConnection(ClickSel a, ClickSel b)
{  
    //Check to make sure that a is the output and b is the input
    if (a.clickType != ClickSel::C_OUT || b.clickType != ClickSel::C_IN)
        return 0;

    SelDat atype;
    atype.selected = SelDat::C_OUT;
    atype.itemnum = a.num;

    SelDat btype;
    btype.selected = SelDat::C_IN;
    btype.itemnum = b.num;


    //Check to make sure that output type of one == input type of other
    if (a.itemClicked->getDatType(atype) != b.itemClicked->getDatType(btype))
        return 0;

    //Check to make sure that input is not already connected
    for (QMap<int, Conns>::iterator i = connections.begin(); i != connections.end(); i++)
    {
        Conns c = *i;

        if (b.itemClicked == c.b.itemClicked && b.num == c.b.num)
            return 0;
    }

    Conns n;
    n.a = a;
    n.b = b;
    connId++;

    connections[connId] = n;

    return connId; //Return the id of the connection if successful
}

/*****************************************************************************
 * Removes the object connected to the view from the map
 *****************************************************************************/
void FilterMap::deleteView(MapObj* itm)
{
    ListType t = itm->getType();
    switch (t)
    {
        case INPUT:
        {
            Input* r = dynamic_cast<Input*>(itm);
            inputs.removeAll(r);
            delete r;
            break;
        }
        case OUTPUT:
        {
            Output* r = dynamic_cast<Output*>(itm);
            outputs.removeAll(r);
            delete r;
            break;
        }
        default:
        {
            Filter* r = dynamic_cast<Filter*>(itm);
            filters.removeAll(r);
            delete r;
            break;
        }
    }
}

/*****************************************************************************
 * Removes the connection with the given id from the map
 *****************************************************************************/
void FilterMap::deleteConnection(int itm)
{
    if (connections.contains(itm))
        connections.remove(itm);
}

/*****************************************************************************
 *
 *****************************************************************************/
void FilterMap::updateSystem()
{
    int max = 0;
    for (int i = 0; i < inputs.size(); i++)
    {
        int num = inputs[i]->getNumFrames();
        if (num < 0)
        {
            maxFrames = -1;
            return;
        }

        if (num > max)
        {
            max = num;
        }
    }
    maxFrames = max;



}

/*****************************************************************************
 * Returns the max number of frames of the
 *****************************************************************************/
int FilterMap::getMaxFrames()
{
    return maxFrames;
}

/*****************************************************************************
 *
 *****************************************************************************/
void FilterMap::fullReset()
{
    for(QList<Filter*>::iterator i = filters.begin(); i != filters.end(); i++)
    {
        Filter* f = *i;
        f->resetToFrameZero();
    }

    for (QList<Input*>::iterator i = inputs.begin(); i != inputs.end(); i++)
    {
        Input* f = *i;
        f->resetToFrameZero();
    }

    for (QList<Output*>::iterator i = outputs.begin(); i != outputs.end(); i++)
    {
        Output* f = *i;
        f->resetToFrameZero();
    }
    currFrame = 0;

}

/*****************************************************************************
 *
 *****************************************************************************/
int FilterMap::runNext()
{
    usleep(30);
    setupForNextFrame();

    QVector<Data*> datpieces;

    //Run through the inputs and take their outputs and send them to the filters
    //or outputs they are connected to
    for (QList<Input*>::iterator i = inputs.begin(); i != inputs.end(); i++)
    {
        Input* f = *i;
        QVector<Data*> datpiece = f->getNextFrame();
        for (int i = 0; i < datpiece.size(); i++)
        {
            datpieces.push_back(datpiece[i]);
        }

        for (QMap<int, Conns>::iterator mapit = connections.begin(); mapit != connections.end(); mapit++)
        {
            Conns c = mapit.value();
            if (c.a.itemClicked->getMapObj() == f)
            {
                Data* d = datpiece[c.a.num];
                c.b.itemClicked->getMapObj()->setNext(d, c.b.num);
            }
        }
    }

    //
    bool done = false;
    int size = filters.size() + outputs.size();
    for (int filtloop = 0; filtloop < size && !done; filtloop++)
    {
        for (QList<Filter*>::iterator i = filters.begin(); i != filters.end(); i++)
        {
            Filter* f = *i;
            if (f->isReadyToRun() && !f->hasRun())
            {
                QVector<Data*> datpiece = f->runObj();
                for (int i = 0; i < datpiece.size(); i++)
                {
                    datpieces.push_back(datpiece[i]);
                }

                for (QMap<int, Conns>::iterator mapit = connections.begin(); mapit != connections.end(); mapit++)
                {
                    Conns c = mapit.value();
                    if (c.a.itemClicked->getMapObj() == f)
                    {
                        Data* d = datpiece[c.a.num];
                        c.b.itemClicked->getMapObj()->setNext(d, c.b.num);
                    }
                }
            }
        }

        done = true;

        for (QList<Output*>::iterator i = outputs.begin(); i != outputs.end(); i++)
        {
            Output* f = *i;
            if (f->isReadyToRun() && !f->hasRun())
            {
                QVector<Data*> datpiece = f->runObj();
                for (int i = 0; i < datpiece.size(); i++)
                {
                    datpieces.push_back(datpiece[i]);
                }

            }
            else if (!f->isReadyToRun())
            {
                done = false;
            }
        }
    }

    for (int i = 0; i < datpieces.size(); i++)
    {
        delete datpieces[i];
        datpieces[i] = NULL;
    }


    return ++currFrame;
}

/*****************************************************************************
 * After an update, runs the current frame again to update any output
 * (Usually video output)
 *****************************************************************************/
int FilterMap::runCurrent()
{
    setupForNextFrame();

    QVector<Data*> datpieces;

    //Run through the inputs and take their outputs and send them to the filters
    //or outputs they are connected to
    for (QList<Input*>::iterator i = inputs.begin(); i != inputs.end(); i++)
    {
        Input* f = *i;
        QVector<Data*> datpiece = f->getCurrentFrame();
        for (int i = 0; i < datpiece.size(); i++)
        {
            datpieces.push_back(datpiece[i]);
        }

        for (QMap<int, Conns>::iterator mapit = connections.begin(); mapit != connections.end(); mapit++)
        {
            Conns c = mapit.value();
            if (c.a.itemClicked->getMapObj() == f)
            {
                Data* d = datpiece[c.a.num];
                c.b.itemClicked->getMapObj()->setNext(d, c.b.num);
            }
        }
    }

    //
    bool done = false;
    int size = filters.size() + outputs.size();
    for (int filtloop = 0; filtloop < size && !done; filtloop++)
    {
        for (QList<Filter*>::iterator i = filters.begin(); i != filters.end(); i++)
        {
            Filter* f = *i;
            if (f->isReadyToRun() && !f->hasRun())
            {
                QVector<Data*> datpiece = f->runObj();
                for (int i = 0; i < datpiece.size(); i++)
                {
                    datpieces.push_back(datpiece[i]);
                }
                for (QMap<int, Conns>::iterator mapit = connections.begin(); mapit != connections.end(); mapit++)
                {
                    Conns c = mapit.value();
                    if (c.a.itemClicked->getMapObj() == f)
                    {
                        Data* d = datpiece[c.a.num];
                        c.b.itemClicked->getMapObj()->setNext(d, c.b.num);
                    }
                }
            }
        }

        done = true;

        for (QList<Output*>::iterator i = outputs.begin(); i != outputs.end(); i++)
        {
            Output* f = *i;
            if (f->isReadyToRun() && !f->hasRun())
            {
                QVector<Data*> datpiece = f->runObj();
                for (int i = 0; i < datpiece.size(); i++)
                {
                    datpieces.push_back(datpiece[i]);
                }
            }
            else if (!f->isReadyToRun())
            {
                done = false;
            }
        }
    }

    for (int i = 0; i < datpieces.size(); i++)
    {
        delete datpieces[i];
        datpieces[i] = NULL;
    }


    return currFrame;
}

/*****************************************************************************
 *
 *****************************************************************************/
void FilterMap::setFrame(int frameNum)
{
    currFrame = frameNum;
    for (QList<Input*>::iterator i = inputs.begin(); i != inputs.end(); i++)
    {
        Input* f = *i;
        f->setFrameNum(frameNum);
    }
}

/*****************************************************************************
 *
 *****************************************************************************/
void FilterMap::cleanAll()
{

}

/*****************************************************************************
 *
 *****************************************************************************/
QVector<connectionOut> FilterMap::getConnections()
{
    QVector<connectionOut> ans;

    for (QMap<int, Conns>::iterator it = connections.begin(); it != connections.end(); it++)
    {
        connectionOut conn;
        Conns i = *it;
        if (i.a.clickType == ClickSel::C_IN)
            conn.type1 = 0;
        else if (i.a.clickType == ClickSel::C_OUT)
            conn.type1 = 1;
        else
            conn.type1 = -1;

        conn.id1 = i.a.itemClicked->getMapObj()->getId();
        conn.item1 = i.a.num;

        if (i.b.clickType == ClickSel::C_IN)
            conn.type2 = 0;
        else if (i.b.clickType == ClickSel::C_OUT)
            conn.type2 = 0;
        else
            conn.type2 = -1;

        conn.id2 = i.b.itemClicked->getMapObj()->getId();
        conn.item2 = i.b.num;

        ans.push_back(conn);
    }

    return ans;
}

