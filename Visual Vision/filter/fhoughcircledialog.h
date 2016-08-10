/*****************************************************************************
 * Copyright Tim Price
 *****************************************************************************/

#ifndef FHOUGHCIRCLEDIALOG_H
#define FHOUGHCIRCLEDIALOG_H

#include <QDialog>

namespace Ui {
class FHoughCircleDialog;
}

/*****************************************************************************
 * Dialog box for the Hough Circle Filter
 *****************************************************************************/
class FHoughCircleDialog : public QDialog
{
        Q_OBJECT

    public:
        explicit FHoughCircleDialog(QWidget *parent = 0);
        ~FHoughCircleDialog();

        double param1();
        double param2();
        int minRadius();
        int maxRadius();
        int minDistance();

        void setParam1(double val);
        void setParam2(double val);
        void setMinRadius(int val);
        void setMaxRadius(int val);
        void setMinDistance(int val);


    private slots:
        void on_cmdOk_clicked();

        void on_cmdCancel_clicked();

    private:
        Ui::FHoughCircleDialog *ui;
        int vMinRadius;
        int vMaxRadius;
        double vParam1;
        double vParam2;
        int vMinDistance;
};

#endif // FHOUGHCIRCLEDIALOG_H
