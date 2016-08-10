/*****************************************************************************
 * Copyright Tim Price
 *****************************************************************************/

#ifndef FGRAYSCALEDIALOG_H
#define FGRAYSCALEDIALOG_H

#include <QDialog>

namespace Ui {
class FGrayscaleDialog;
}

/*****************************************************************************
 *
 *****************************************************************************/
class FGrayscaleDialog : public QDialog
{
    Q_OBJECT

    public:
        explicit FGrayscaleDialog(QWidget *parent = 0);
        ~FGrayscaleDialog();

    private:
        Ui::FGrayscaleDialog *ui;
};

#endif // FGRAYSCALEDIALOG_H
