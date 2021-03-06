#include "flaplaciandialog.h"
#include "ui_flaplaciandialog.h"

/*****************************************************************************
 *
 *****************************************************************************/
FLaplacianDialog::FLaplacianDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FLaplacianDialog)
{
    ui->setupUi(this);
}

/*****************************************************************************
 *
 *****************************************************************************/
FLaplacianDialog::~FLaplacianDialog()
{
    delete ui;
}

/*****************************************************************************
 *
 *****************************************************************************/
int FLaplacianDialog::getKernelSize()
{
    return vKernelSize;
}

/*****************************************************************************
 *
 *****************************************************************************/
void FLaplacianDialog::setKernelSize(int val)
{
    vKernelSize = val;
}

/*****************************************************************************
 *
 *****************************************************************************/
void FLaplacianDialog::on_cmdOk_clicked()
{
    switch (ui->cboKernel->currentIndex())
    {

    }
}

/*****************************************************************************
 *
 *****************************************************************************/
void FLaplacianDialog::on_cmdCancel_clicked()
{

}
