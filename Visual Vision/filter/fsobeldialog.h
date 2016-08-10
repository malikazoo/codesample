/*****************************************************************************
 * Copyright Tim Price
 *****************************************************************************/

#ifndef FSOBELDIALOG_H
#define FSOBELDIALOG_H

#include <QDialog>

#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

namespace Ui {
class FSobelDialog;
}

/*****************************************************************************
 *
 *****************************************************************************/
class FSobelDialog : public QDialog
{
    Q_OBJECT

    public:
        explicit FSobelDialog(QWidget *parent = 0);
        ~FSobelDialog();

        QString getType();
        int getKernelSize();

        void setType(QString val);
        void setKernelSize(int val);

    protected:
        void showEvent(QShowEvent *);

    private slots:
        void on_cmdCancel_clicked();
        void on_cmdOk_clicked();

    private:
        Ui::FSobelDialog *ui;
        int vKernelSize;
        QString vtype;
        bool scharrClicked;
};

#endif // FSOBELDIALOG_H
