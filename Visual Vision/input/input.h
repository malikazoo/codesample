/*****************************************************************************
 * Copyright Tim Price
 *****************************************************************************/

#ifndef INPUT_H
#define INPUT_H

#include <QObject>

#include "data/data.h"
#include "vview.h"
#include "mapobj.h"

#include <QJsonObject>

/*****************************************************************************
 * Input base class
 * Will provide data for input into the system.
 *****************************************************************************/
class Input : public MapObj
{
    Q_OBJECT

    public:
        explicit Input(QObject *parent = 0);
        ~Input();

        ListType getType();
        QSize getBaseSize();

        virtual int getNumFrames() = 0;

        virtual QVector<Data*> getNextFrame() = 0;
        virtual QVector<Data*> getCurrentFrame() = 0;
        virtual void setFrameNum(int framenum) = 0;

        virtual QVector<DatInfo> getInputTypes();
        virtual QVector<DatInfo> getOutputTypes() = 0;

        QMap<QString, QVariant> getRep();
        void setRep(QMap<QString, QVariant> rep);

    protected:

        virtual QMap<QString, QVariant> getData() = 0;
        virtual void setData(QMap<QString, QVariant> data) = 0;
        virtual void reset() = 0;
        virtual QVector<Data*> run(QVector<Data*>);
};

#endif // INPUT_H
