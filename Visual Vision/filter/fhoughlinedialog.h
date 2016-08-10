/*****************************************************************************
 * Copyright Tim Price
 *****************************************************************************/

#ifndef FHOUGHLINEDIALOG_H
#define FHOUGHLINEDIALOG_H

#include <QDialog>

namespace Ui {
class FHoughLineDialog;
}

class FHoughLineDialog : public QDialog
{
        Q_OBJECT

    public:
        explicit FHoughLineDialog(QWidget *parent = 0);
        ~FHoughLineDialog();

        double getRho();
        double getTheta();
        int getThreshold();
        double getMinLineLength();
        double getMaxLineGap();

        void setRho(double val);
        void setTheta(double val);
        void setThreshold(int val);
        void setMinLineLength(double val);
        void setMaxLineGap(double val);


    protected:
        void showEvent(QShowEvent *);

    private slots:
        void on_cmdOk_clicked();

        void on_cmdCancel_clicked();

    private:
        Ui::FHoughLineDialog *ui;
        double vRho;
        double vTheta;
        int vThresh;
        double vMinLineLength;
        double vMaxLineGap;
};

#endif // FHOUGHLINEDIALOG_H
