/*****************************************************************************
 * Copyright Tim Price
 *****************************************************************************/

#ifndef FCOLORDIALOG_H
#define FCOLORDIALOG_H

#include <QDialog>
#include <QDebug>

namespace Ui {
class FColorDialog;
}


/*****************************************************************************
 *
 *****************************************************************************/
class FColorDialog : public QDialog
{
    Q_OBJECT

    public:
        explicit FColorDialog(QWidget *parent = 0);
        ~FColorDialog();

        double amountRed();
        double amountGreen();
        double amountBlue();

        void setRed(double val);
        void setGreen(double val);
        void setBlue(double val);


    private slots:
        void on_cmdOk_clicked();
        void on_cmdCancel_clicked();


        void on_sldRed_sliderMoved(int position);

        void on_sldGreen_sliderMoved(int position);

        void on_sldBlue_sliderMoved(int position);

        void on_dblRed_editingFinished();

        void on_dblGreen_editingFinished();

        void on_dblBlue_editingFinished();

    private:
        Ui::FColorDialog *ui;

        double red;
        double green;
        double blue;

};

#endif // FCOLORDIALOG_H
