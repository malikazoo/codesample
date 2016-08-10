/*****************************************************************************
 * Copyright Tim Price
 *****************************************************************************/

#ifndef ICAMERADIALOG_H
#define ICAMERADIALOG_H

#include <QDialog>

namespace Ui {
class ICameraDialog;
}

class ICameraDialog : public QDialog
{
        Q_OBJECT

    public:
        explicit ICameraDialog(QWidget *parent = 0);
        ~ICameraDialog();

        int getCameraId();
        bool OkClicked();

        void setCameraId(int id);

        void showEvent(QShowEvent *);



    private slots:
        void on_cmdOk_clicked();

        void on_cmdCancel_clicked();

    private:
        Ui::ICameraDialog *ui;
        int cameraId;
        bool vOkClicked;
};

#endif // ICAMERADIALOG_H
