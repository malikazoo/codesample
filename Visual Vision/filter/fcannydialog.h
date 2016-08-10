/*****************************************************************************
 * Copyright Tim Price
 *****************************************************************************/

#ifndef FCANNYDIALOG_H
#define FCANNYDIALOG_H

#include <QDialog>

namespace Ui {
class FCannyDialog;
}


/*****************************************************************************
 *
 *****************************************************************************/
class FCannyDialog : public QDialog
{
        Q_OBJECT

    public:
        explicit FCannyDialog(QWidget *parent = 0);
        ~FCannyDialog();


        double getThresh1();
        double getThresh2();
        int getKernelSize();

        void setThresh1(double val);
        void setThresh2(double val);
        void setKernelSize(int val);


        void showEvent(QShowEvent *);


    private slots:
        void on_cmdOk_clicked();

        void on_cmdCancel_clicked();

    private:
        Ui::FCannyDialog *ui;

        double thresh1;
        double thresh2;
        int kernel;

};

#endif // FCANNYDIALOG_H
