/*****************************************************************************
 * Copyright Tim Price
 *****************************************************************************/

#ifndef FDRAWLINESDIALOG_H
#define FDRAWLINESDIALOG_H

#include <QDialog>
#include <QColorDialog>

namespace Ui {
class FDrawLinesDialog;
}

class FDrawLinesDialog : public QDialog
{
        Q_OBJECT

    public:
        explicit FDrawLinesDialog(QWidget *parent = 0);
        ~FDrawLinesDialog();

        QColor getSelectedColor();
        int getWidth();

        void setColor(QColor col);
        void setWidth(int width);


    private slots:
        void on_cmdOk_clicked();

        void on_cmdCancel_clicked();

        void on_cmdColor_clicked();

    private:
        Ui::FDrawLinesDialog *ui;
        QColor vCol;
        int vWidth;
};

#endif // FDRAWLINESDIALOG_H
