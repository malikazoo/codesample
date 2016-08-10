/*****************************************************************************
 * Copyright Tim Price
 *****************************************************************************/

#ifndef FCOMBINEDIALOG_H
#define FCOMBINEDIALOG_H

#include <QDialog>

namespace Ui {
class FCombineDialog;
}


/*****************************************************************************
 *
 *****************************************************************************/
class FCombineDialog : public QDialog
{
    Q_OBJECT

    public:
        explicit FCombineDialog(QWidget *parent = 0);
        ~FCombineDialog();

    private:
        Ui::FCombineDialog *ui;
};

#endif // FCOMBINEDIALOG_H
