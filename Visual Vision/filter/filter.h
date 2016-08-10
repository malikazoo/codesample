/*****************************************************************************
 * Copyright Tim Price
 *****************************************************************************/

#ifndef FILTER_H
#define FILTER_H

#include <QObject>
#include <QPoint>
#include <QString>
#include <QVector>
#include <QJsonObject>

#include "mapobj.h"

#include "data/data.h"
#include "data/dimage1.h"
#include "data/dimage3.h"
#include "data/dline.h"
#include "data/dnone.h"
#include "data/dpoint.h"
#include "data/dhistogram.h"

#include "general.h"

/*****************************************************************************
 * The base filter function,
 *****************************************************************************/
class Filter : public MapObj
{
    Q_OBJECT

    public:
        explicit Filter(QObject *parent = 0);
        ~Filter();
        ListType getType();

        void setPos(QPointF pnt);

        static QString getName();
        QSize getBaseSize();

        static FiltList getList();

        virtual QVector<DatInfo> getInputTypes() = 0;
        virtual QVector<DatInfo> getOutputTypes() = 0;

        QMap<QString, QVariant> getRep();
        void setRep(QMap<QString, QVariant> rep);

    signals:

    public slots:

    protected:
        virtual QMap<QString, QVariant> getData() = 0;
        virtual void setData(QMap<QString, QVariant> data) = 0;
        virtual void reset() = 0;
        virtual QVector<Data*> run(QVector<Data*> dat) = 0;

    private:


};

#endif // FILTER_H
