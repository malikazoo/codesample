/*****************************************************************************
 * Copyright Tim Price
 *****************************************************************************/

#ifndef FBLURDIALOG_H
#define FBLURDIALOG_H

#include <QDialog>

namespace Ui {
class FBlurDialog;
}


/*****************************************************************************
 * Dialog box for Blur filter.  Allows a user to choose type of blur as well
 * as setting parameters for the blur
 *
 * PARAMETERS:
 *  Kernel size
 *  Sigma
 *  Blur Type
 *****************************************************************************/
class FBlurDialog : public QDialog
{
        Q_OBJECT

    public:
        explicit FBlurDialog(QWidget *parent = 0);
        ~FBlurDialog();

        enum BLURTYPE {UNIFORM, GAUSSIAN, MEDIAN};

        int getKernelX();
        int getKernelY();
        double getSigmaX();
        double getSigmaY();
        BLURTYPE getBlurType();

        void setKernelX(int val);
        void setKernelY(int val);
        void setSigmaX(double val);
        void setSigmaY(double val);
        void setBlurType(BLURTYPE type);


        void showEvent(QShowEvent *);

    private slots:
        void on_cmdOk_clicked();
        void on_cmdCancel_clicked();

        void on_cboType_currentIndexChanged(int index);

    private:
        Ui::FBlurDialog *ui;

        BLURTYPE getType(int type);

        BLURTYPE vType;
        int kernelX;
        int kernelY;
        double sigmaX;
        double sigmaY;

};

#endif // FBLURDIALOG_H
