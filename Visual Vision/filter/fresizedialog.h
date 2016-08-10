/*****************************************************************************
 * Copyright Tim Price
 *****************************************************************************/

#ifndef FRESIZEDIALOG_H
#define FRESIZEDIALOG_H

#include <QDialog>

namespace Ui {
class FResizeDialog;
}

/*****************************************************************************
 *
 *****************************************************************************/
class FResizeDialog : public QDialog
{
        Q_OBJECT

    public:
        explicit FResizeDialog(QWidget *parent = 0);
        ~FResizeDialog();

        int getX();
        int getY();

        void setX(int x);
        void setY(int y);

        void showEvent(QShowEvent *);

    private slots:
        void on_cmdOk_clicked();

        void on_cmdCancel_clicked();

    private:
        Ui::FResizeDialog *ui;

        int vX;
        int vY;
};

#endif // FRESIZEDIALOG_H
