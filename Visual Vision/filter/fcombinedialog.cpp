#include "fcombinedialog.h"
#include "ui_fcombinedialog.h"

/*****************************************************************************
 *
 *****************************************************************************/
FCombineDialog::FCombineDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FCombineDialog)
{
    ui->setupUi(this);
}

/*****************************************************************************
 *
 *****************************************************************************/
FCombineDialog::~FCombineDialog()
{
    delete ui;
}
