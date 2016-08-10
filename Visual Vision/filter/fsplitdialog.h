/*****************************************************************************
 * Copyright Tim Price
 *****************************************************************************/

#ifndef FSPLITDIALOG_H
#define FSPLITDIALOG_H

#include <QDialog>

namespace Ui {
class FSplitDialog;
}

/*****************************************************************************
 *
 *****************************************************************************/
class FSplitDialog : public QDialog
{
    Q_OBJECT

    public:
        explicit FSplitDialog(QWidget *parent = 0);
        ~FSplitDialog();

    private:
        Ui::FSplitDialog *ui;
};

#endif // FSPLITDIALOG_H
