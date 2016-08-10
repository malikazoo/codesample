/*****************************************************************************
 * Copyright Tim Price
 *****************************************************************************/

#ifndef FDISTANCEDIALOG_H
#define FDISTANCEDIALOG_H

#include <QDialog>

#include "general.h"

namespace Ui {
class FDistanceDialog;
}

class FDistanceDialog : public QDialog
{
        Q_OBJECT

    public:
        explicit FDistanceDialog(QWidget *parent = 0);
        ~FDistanceDialog();

        enum FDISTANCE {DIST_EUCLIDEAN, DIST_MANHATTAN, DIST_CHEBYSHEV};

        FDistanceDialog::FDISTANCE getType();

        void showEvent(QShowEvent *);
        
        void setType(FDistanceDialog::FDISTANCE type);

    private slots:
        void on_cmdOk_clicked();

        void on_cmdCancel_clicked();

    private:
        Ui::FDistanceDialog *ui;
        FDISTANCE vType;


};

#endif // FDISTANCEDIALOG_H
