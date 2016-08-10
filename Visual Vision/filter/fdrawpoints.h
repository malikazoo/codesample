/*****************************************************************************
 * Copyright Tim Price
 *****************************************************************************/

#ifndef FDRAWPOINTS_H
#define FDRAWPOINTS_H

#include "filter.h"
#include "filterfactory.h"
#include "fdrawpointsdialog.h"

class FDrawPoints : public Filter
{
        Q_OBJECT
    public:
        explicit FDrawPoints(QObject *parent = 0);


        static QString getName();
        QString getCaption();

        virtual QVector<DatInfo> getInputTypes();
        virtual QVector<DatInfo> getOutputTypes();

        void showConfig();

    signals:

    public slots:

    private:
        QMap<QString, QVariant> getData();
        void setData(QMap<QString, QVariant> data);
        FDrawPointsDialog dialog;
        void reset();
        QVector<Data*> run(QVector<Data*> dat);

};

#endif // FDRAWPOINTS_H
