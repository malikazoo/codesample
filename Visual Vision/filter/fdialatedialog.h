/*****************************************************************************
 * Copyright Tim Price
 *****************************************************************************/

#ifndef FDIALATEDIALOG_H
#define FDIALATEDIALOG_H

#include <QDialog>


namespace Ui {
class FDialateDialog;
}

/*****************************************************************************
 *
 *****************************************************************************/
class FDialateDialog : public QDialog
{
        Q_OBJECT

    public:
        explicit FDialateDialog(QWidget *parent = 0);
        ~FDialateDialog();

        enum DIALATETYPE {RECTANGLE, CROSS, ELLIPSE};
        DIALATETYPE getDialateType();
        int getSizeX();
        int getSizeY();

        void setDialateType(DIALATETYPE type);
        void setSizeX(int val);
        void setSizeY(int val);


    private slots:
        void on_cmdOk_clicked();
        void on_cmdCancel_clicked();



    private:
        Ui::FDialateDialog *ui;
        DIALATETYPE getType(int type);
        int getType(DIALATETYPE type);
        DIALATETYPE vType;
        int vSizeX;
        int vSizeY;
};

#endif // FDIALATEDIALOG_H
