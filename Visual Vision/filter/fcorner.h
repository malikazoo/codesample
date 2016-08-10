/*****************************************************************************
 * Copyright Tim Price
 *****************************************************************************/

#ifndef FCORNER_H
#define FCORNER_H

#include "filter.h"
#include "filterfactory.h"
#include "fcornerdialog.h"



class FCorner : public Filter
{
        Q_OBJECT
    public:
        explicit FCorner(QObject *parent = 0);

        static QString getName();
        QString getCaption();

        virtual QVector<DatInfo> getInputTypes();
        virtual QVector<DatInfo> getOutputTypes();

        void showConfig();


    protected:
        QMap<QString, QVariant> getData();
        void setData(QMap<QString, QVariant> data);
        FCornerDialog dialog;
        void reset();
        QVector<Data*> run(QVector<Data*> dat);

    signals:

    public slots:

};

#endif // FCORNER_H
