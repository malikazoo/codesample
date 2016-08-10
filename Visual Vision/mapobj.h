/*****************************************************************************
 * Copyright Tim Price
 *****************************************************************************/

#ifndef MAPOBJ_H
#define MAPOBJ_H

#include <QObject>
#include "general.h"
#include "data/data.h"

/*****************************************************************************
 * The base class used for all filters, inputs and outputs
 * Interface
 *****************************************************************************/
class MapObj : public QObject
{
        Q_OBJECT
    public:
        explicit MapObj(QObject *parent = 0);

        virtual ListType getType() = 0;
        virtual QString getCaption() = 0;
        virtual QSize getBaseSize() = 0;
        virtual QVector<DatInfo> getInputTypes() = 0;
        virtual QVector<DatInfo> getOutputTypes() = 0;
        virtual void showConfig() = 0;
        virtual void setNext(Data* frame, int location);
        virtual bool isReadyToRun();
        virtual void setupNextFrame();
        virtual void resetToFrameZero();
        virtual QVector<Data*> runObj();
        virtual bool hasRun();

        virtual QMap<QString, QVariant> getRep() = 0;

        void setId(int id);
        int getId();



    protected:
        QVector<Data*> vdat;
        bool vhasrun;

        virtual void reset() = 0;
        virtual QVector<Data*> run(QVector<Data*> dat) = 0;

    signals:

    public slots:

    private:
        int vId;
        static int numMap;

};

#endif // MAPOBJ_H
