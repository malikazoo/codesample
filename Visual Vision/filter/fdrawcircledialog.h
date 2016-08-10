/*****************************************************************************
 * Copyright Tim Price
 *****************************************************************************/

#ifndef FDRAWCIRCLEDIALOG_H
#define FDRAWCIRCLEDIALOG_H

#include <QDialog>
#include <QColorDialog>

namespace Ui {
class FDrawCircleDialog;
}

/*****************************************************************************
 * Dialog box the shows up to edit the draw circle filter
 *****************************************************************************/
class FDrawCircleDialog : public QDialog
{
        Q_OBJECT

    public:
        explicit FDrawCircleDialog(QWidget *parent = 0);
        ~FDrawCircleDialog();

        QColor getColor();
        int getWidth();

        void setColor(QColor col);
        void setWidth(int width);

    private slots:
        void on_cmdColor_clicked();

        void on_cmdOk_clicked();

        void on_cmdCancel_clicked();

    private:
        Ui::FDrawCircleDialog *ui;
        QColor vCol;
        int vWidth;
};

#endif // FDRAWCIRCLEDIALOG_H
