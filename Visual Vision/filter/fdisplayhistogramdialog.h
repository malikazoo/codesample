/*****************************************************************************
 * Copyright Tim Price
 *****************************************************************************/

#ifndef FDISPLAYHISTOGRAMDIALOG_H
#define FDISPLAYHISTOGRAMDIALOG_H

#include <QDialog>
#include <QColor>
#include <QColorDialog>

namespace Ui {
class FDisplayHistogramDialog;
}

/*****************************************************************************
 *
 *****************************************************************************/
class FDisplayHistogramDialog : public QDialog
{
        Q_OBJECT

    public:
        explicit FDisplayHistogramDialog(QWidget *parent = 0);
        ~FDisplayHistogramDialog();

        int getWidth();
        int getHeight();
        QColor getForeColor();
        QColor getBackColor();

        void setWidth(int val);
        void setHeight(int val);
        void setForeColor(QColor col);
        void setBackColor(QColor col);

        void showEvent(QShowEvent *);

    private slots:
        void on_cmdOk_clicked();

        void on_cmdCancel_clicked();

        void on_cmdBackColor_clicked();

        void on_cmdForeColor_clicked();

    private:
        Ui::FDisplayHistogramDialog *ui;

        int vWidth;
        int vHeight;
        QColor vBack;
        QColor vFore;

        QColor vTempBack;
        QColor vTempFore;
};

#endif // FDISPLAYHISTOGRAMDIALOG_H
