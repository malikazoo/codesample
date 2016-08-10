/*****************************************************************************
 * Copyright Tim Price
 *****************************************************************************/

#ifndef OUTPUT_H
#define OUTPUT_H

#include <QJsonObject>

#include "data/data.h"

#include "vview.h"
#include "mapobj.h"

#include "data/data.h"
#include "data/dimage1.h"
#include "data/dimage3.h"
#include "data/dline.h"
#include "data/dnone.h"
#include "data/dpoint.h"

/*****************************************************************************
 * An end point.  This will take a given data piece and output it
 *****************************************************************************/
class Output : public MapObj
{
    Q_OBJECT

    public:
        explicit Output(QObject* parent = 0);
        ~Output();
        ListType getType();
        QSize getBaseSize();

        void setPos(QPointF pnt);

        VView* getOutputView();

        virtual QVector<DatInfo> getInputTypes() = 0;
        virtual QVector<DatInfo> getOutputTypes();

        QMap<QString, QVariant> getRep();
        void setRep(QMap<QString, QVariant> rep);

    protected:
        virtual QMap<QString, QVariant> getData() = 0;
        virtual void setData(QMap<QString, QVariant> data) = 0;
        virtual void reset() = 0;
        virtual QVector<Data*> run(QVector<Data*> dat) = 0;

    private slots:

};

#endif // OUTPUT_H
