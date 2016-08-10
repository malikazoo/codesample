#include "fsobeldialog.h"
#include "ui_fsobeldialog.h"

/*****************************************************************************
 *
 *****************************************************************************/
FSobelDialog::FSobelDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FSobelDialog)
{
    ui->setupUi(this);

    vtype = "X";
    vKernelSize = 3;
    ui->cboDirection->setCurrentText(vtype);
    ui->spnKernel->setValue(3);
    scharrClicked = false;
}

/*****************************************************************************
 *
 *****************************************************************************/
FSobelDialog::~FSobelDialog()
{
    delete ui;
}

/*****************************************************************************
 *
 *****************************************************************************/
QString FSobelDialog::getType()
{
    return vtype;
}

/*****************************************************************************
 *
 *****************************************************************************/
int FSobelDialog::getKernelSize()
{
    if (scharrClicked)
        return CV_SCHARR;
    else
        return vKernelSize;
}

/*****************************************************************************
 *
 *****************************************************************************/
void FSobelDialog::setType(QString val)
{
    vtype = val;
}

/*****************************************************************************
 *
 *****************************************************************************/
void FSobelDialog::setKernelSize(int val)
{
    if (val == CV_SCHARR)
    {
        scharrClicked = true;
    }
    else
    {
        vKernelSize = val;
    }
}

/*****************************************************************************
 *
 *****************************************************************************/
void FSobelDialog::showEvent(QShowEvent*)
{
    ui->cboDirection->setCurrentText(vtype);
    ui->spnKernel->setValue(vKernelSize);
    ui->chkScharr->setChecked(scharrClicked);
}

/*****************************************************************************
 *
 *****************************************************************************/
void FSobelDialog::on_cmdCancel_clicked()
{
    ui->cboDirection->setCurrentText(vtype);
    ui->spnKernel->setValue(vKernelSize);
    ui->chkScharr->setChecked(scharrClicked);
    close();
}

/*****************************************************************************
 *
 *****************************************************************************/
void FSobelDialog::on_cmdOk_clicked()
{
    vtype = ui->cboDirection->currentText();
    vKernelSize = ui->spnKernel->value();
    scharrClicked = ui->chkScharr->isChecked();
    close();
}
