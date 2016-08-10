#include "fsplitdialog.h"
#include "ui_fsplitdialog.h"

/*****************************************************************************
 *
 *****************************************************************************/
FSplitDialog::FSplitDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FSplitDialog)
{
    ui->setupUi(this);
}

/*****************************************************************************
 *
 *****************************************************************************/
FSplitDialog::~FSplitDialog()
{
    delete ui;
}
