#include "fblurdialog.h"
#include "ui_fblurdialog.h"

/*****************************************************************************
 * Default Constructor, Sets the blur to uniform
 *****************************************************************************/
FBlurDialog::FBlurDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FBlurDialog)
{
    ui->setupUi(this);
    vType = UNIFORM;
    kernelX = 3;
    kernelY = 3;
    sigmaX = 0;
    sigmaY = 0;
}

/*****************************************************************************
 *
 *****************************************************************************/
FBlurDialog::~FBlurDialog()
{
    delete ui;
}

/*****************************************************************************
 * Returns x parameter of the kernel
 *****************************************************************************/
int FBlurDialog::getKernelX()
{
    return kernelX;
}

/*****************************************************************************
 * Returns y parameter of the kernel
 *****************************************************************************/
int FBlurDialog::getKernelY()
{
    return kernelY;
}

/*****************************************************************************
 *
 *****************************************************************************/
double FBlurDialog::getSigmaX()
{
    return sigmaX;
}

/*****************************************************************************
 *
 *****************************************************************************/
double FBlurDialog::getSigmaY()
{
    return sigmaY;
}

/*****************************************************************************
 *
 *****************************************************************************/
FBlurDialog::BLURTYPE FBlurDialog::getBlurType()
{
    return vType;
}

/*****************************************************************************
 *
 *****************************************************************************/
void FBlurDialog::setKernelX(int val)
{
    kernelX = val;
}

/*****************************************************************************
 *
 *****************************************************************************/
void FBlurDialog::setKernelY(int val)
{
    kernelY = val;
}

/*****************************************************************************
 *
 *****************************************************************************/
void FBlurDialog::setSigmaX(double val)
{
    sigmaX = val;
}

/*****************************************************************************
 *
 *****************************************************************************/
void FBlurDialog::setSigmaY(double val)
{
    sigmaY = val;
}

/*****************************************************************************
 *
 *****************************************************************************/
void FBlurDialog::setBlurType(FBlurDialog::BLURTYPE type)
{
    vType = type;
}

/*****************************************************************************
 *
 *****************************************************************************/
void FBlurDialog::showEvent(QShowEvent*)
{
    ui->spnKernelX->setValue(kernelX);
    ui->spnKernelY->setValue(kernelY);
    ui->spnSigmaX->setValue(sigmaX);
    ui->spnSigmaY->setValue(sigmaY);
}

/*****************************************************************************
 *
 *****************************************************************************/
void FBlurDialog::on_cmdOk_clicked()
{
    kernelX = ui->spnKernelX->value();
    kernelY = ui->spnKernelY->value();
    sigmaX = ui->spnSigmaX->value();
    sigmaY = ui->spnSigmaY->value();
    vType = getType(ui->cboType->currentIndex());
    close();
}

/*****************************************************************************
 *
 *****************************************************************************/
void FBlurDialog::on_cmdCancel_clicked()
{
    ui->spnKernelX->setValue(kernelX);
    ui->spnKernelY->setValue(kernelY);
    ui->spnSigmaX->setValue(sigmaX);
    ui->spnSigmaY->setValue(sigmaY);
    close();
}

/*****************************************************************************
 *
 *****************************************************************************/
void FBlurDialog::on_cboType_currentIndexChanged(int index)
{
    switch(getType(index))
    {
        case UNIFORM:
            ui->spnSigmaX->setEnabled(false);
            ui->spnSigmaY->setEnabled(false);
            break;
        case GAUSSIAN:
            ui->spnSigmaX->setEnabled(true);
            ui->spnSigmaY->setEnabled(true);
            break;
        case MEDIAN:
            ui->spnSigmaX->setEnabled(false);
            ui->spnSigmaY->setEnabled(false);
            break;
    }

}

/*****************************************************************************
 *
 *****************************************************************************/
FBlurDialog::BLURTYPE FBlurDialog::getType(int type)
{
    BLURTYPE t;

    switch (type)
    {
        case 0:
            t = UNIFORM;
            break;
        case 1:
            t = GAUSSIAN;
            break;
        default:
            t = MEDIAN;
            break;
    }
    return t;
}
