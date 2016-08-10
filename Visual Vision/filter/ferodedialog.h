/*****************************************************************************
 * Copyright Tim Price
 *****************************************************************************/

#ifndef FERODEDIALOG_H
#define FERODEDIALOG_H

#include <QDialog>

namespace Ui {
class FErodeDialog;
}

/*****************************************************************************
 *
 *****************************************************************************/
class FErodeDialog : public QDialog
{
        Q_OBJECT

    public:
        explicit FErodeDialog(QWidget *parent = 0);
        ~FErodeDialog();

        enum ERODETYPE {RECTANGLE, CROSS, ELLIPSE};
        ERODETYPE getErodeType();
        int getSizeX();
        int getSizeY();

        void setErodeType(ERODETYPE type);
        void setSizeX(int val);
        void setSizeY(int val);


    private slots:
        void on_cmdOk_clicked();

        void on_cmdCancel_clicked();

    private:
        Ui::FErodeDialog *ui;
        ERODETYPE vType;
        int sizeX;
        int sizeY;
        ERODETYPE getType(int type);
        int getType(ERODETYPE type);


};

#endif // FERODEDIALOG_H
