/*****************************************************************************
 * Copyright Tim Price
 *****************************************************************************/

#ifndef FTHRESHOLDDIALOG_H
#define FTHRESHOLDDIALOG_H

#include <QDialog>

namespace Ui {
class FThresholdDialog;
}

/*****************************************************************************
 *
 *****************************************************************************/
class FThresholdDialog : public QDialog
{
        Q_OBJECT

    public:
        explicit FThresholdDialog(QWidget *parent = 0);
        ~FThresholdDialog();

        int getType();
        int getValue();

        void setType(int val);
        void setValue(int val);

        void showEvent(QShowEvent *);

    private slots:
        void on_cmdOk_clicked();

        void on_cmdCancel_clicked();

    private:
        Ui::FThresholdDialog *ui;

        int vType;
        int vValue;


};

#endif // FTHRESHOLDDIALOG_H
