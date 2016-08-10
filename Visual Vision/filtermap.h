/*****************************************************************************
 * Copyright Tim Price
 *****************************************************************************/

#ifndef FILTERMAP_H
#define FILTERMAP_H

#include <QObject>
#include <QDebug>
#include <unistd.h>

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include "filter/filter.h"
#include "input/input.h"
#include "output/output.h"

/*****************************************************************************
 * An filter item that has been selected
 *****************************************************************************/
struct ClickSel
{
    ClickSel(){itemClicked = NULL; clickType = ClickSel::C_NONE;}

    VView* itemClicked;
    enum {C_NONE, C_IN, C_OUT} clickType;
    int num;
};

/*****************************************************************************
 * A line connection
 *****************************************************************************/
struct Conns
{
    ClickSel a;
    ClickSel b;
};

struct connectionOut
{
    //Type, 0 is input, 1 is output
    int type1;
    int id1;
    int item1;
    int type2;
    int id2;
    int item2;
};

/*****************************************************************************
 * The map that holds how the filters are connected to each other and the
 * inputs and outputs
 *****************************************************************************/
class FilterMap : public QObject
{
    Q_OBJECT

    public:
        static FilterMap* getInstance();
        ~FilterMap();
        void addFilter(Filter* filt);
        void addOutput(Output* filt);
        void addInput(Input* filt);

        int createConnection(ClickSel a, ClickSel b);
        void deleteView(MapObj* itm);
        void deleteConnection(int itm);

        void updateSystem();
        int getMaxFrames();
        void fullReset();
        int runNext();
        int runCurrent();
        void setFrame(int frameNum);

        void cleanAll();

        QVector<connectionOut> getConnections();

    signals:

    public slots:

    private:
        explicit FilterMap(QObject *parent = 0);
        QList<Filter*> filters;
        QList<Input*> inputs;
        QList<Output*> outputs;
        int connId;
        QMap<int, Conns> connections;

        static FilterMap* instance;

        int currFrame;
        int maxFrames;

        void setupForNextFrame();

};

#endif // FILTERMAP_H
