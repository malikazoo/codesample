/*****************************************************************************
 * Copyright Tim Price
 *****************************************************************************/

#ifndef FLAPLACIANDIALOG_H
#define FLAPLACIANDIALOG_H

#include <QDialog>

namespace Ui {
class FLaplacianDialog;
}

/*****************************************************************************
 *
 *****************************************************************************/
class FLaplacianDialog : public QDialog
{
        Q_OBJECT

    public:
        explicit FLaplacianDialog(QWidget *parent = 0);
        ~FLaplacianDialog();

        int getKernelSize();

        void setKernelSize(int val);

    private slots:
        void on_cmdOk_clicked();

        void on_cmdCancel_clicked();

    private:
        Ui::FLaplacianDialog *ui;
        int vKernelSize;
};

#endif // FLAPLACIANDIALOG_H
