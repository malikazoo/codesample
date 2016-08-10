#include "fgrayscaledialog.h"
#include "ui_fgrayscaledialog.h"

/*****************************************************************************
 *
 *****************************************************************************/
FGrayscaleDialog::FGrayscaleDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FGrayscaleDialog)
{
    ui->setupUi(this);
}

/*****************************************************************************
 *
 *****************************************************************************/
FGrayscaleDialog::~FGrayscaleDialog()
{
    delete ui;
}
