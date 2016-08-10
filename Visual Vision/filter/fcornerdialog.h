/*****************************************************************************
 * Copyright Tim Price
 *****************************************************************************/

#ifndef FCORNERDIALOG_H
#define FCORNERDIALOG_H

#include <QDialog>


namespace Ui {
class FCornerDialog;
}

class FCornerDialog : public QDialog
{
        Q_OBJECT

    public:
        explicit FCornerDialog(QWidget *parent = 0);
        ~FCornerDialog();

    private:
        Ui::FCornerDialog *ui;
};

#endif // FCORNERDIALOG_H
