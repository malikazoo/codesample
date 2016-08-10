#include "fhoughlinedialog.h"
#include "ui_fhoughlinedialog.h"

/*****************************************************************************
 *
 *****************************************************************************/
FHoughLineDialog::FHoughLineDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FHoughLineDialog)
{
    ui->setupUi(this);
    vRho = 1;
    vTheta = 1;
    vThresh = 50;
    vMinLineLength = 30;
    vMaxLineGap = 10;

    ui->spnRho->setValue(vRho);
    ui->spnTheta->setValue(vTheta);
    ui->spnThresh->setValue(vThresh);
    ui->spnMinLineLength->setValue(vMinLineLength);
    ui->spnMaxLineGap->setValue(vMaxLineGap);

}

/*****************************************************************************
 *
 *****************************************************************************/
FHoughLineDialog::~FHoughLineDialog()
{
    delete ui;
}

/*****************************************************************************
 *
 *****************************************************************************/
double FHoughLineDialog::getRho()
{
    return vRho;
}

/*****************************************************************************
 *
 *****************************************************************************/
double FHoughLineDialog::getTheta()
{
    return vTheta;
}

/*****************************************************************************
 *
 *****************************************************************************/
int FHoughLineDialog::getThreshold()
{
    return vThresh;
}

/*****************************************************************************
 *
 *****************************************************************************/
double FHoughLineDialog::getMinLineLength()
{
    return vMinLineLength;
}

/*****************************************************************************
 *
 *****************************************************************************/
double FHoughLineDialog::getMaxLineGap()
{
    return vMaxLineGap;
}

/*****************************************************************************
 *
 *****************************************************************************/
void FHoughLineDialog::setRho(double val)
{
    vRho = val;
}

/*****************************************************************************
 *
 *****************************************************************************/
void FHoughLineDialog::setTheta(double val)
{
    vTheta = val;
}

/*****************************************************************************
 *
 *****************************************************************************/
void FHoughLineDialog::setThreshold(int val)
{
    vThresh = val;
}

/*****************************************************************************
 *
 *****************************************************************************/
void FHoughLineDialog::setMinLineLength(double val)
{
    vMinLineLength = val;
}

/*****************************************************************************
 *
 *****************************************************************************/
void FHoughLineDialog::setMaxLineGap(double val)
{
    vMaxLineGap = val;
}

/*****************************************************************************
 *
 *****************************************************************************/
void FHoughLineDialog::showEvent(QShowEvent*)
{
    ui->spnRho->setValue(vRho);
    ui->spnTheta->setValue(vTheta);
    ui->spnThresh->setValue(vThresh);
    ui->spnMinLineLength->setValue(vMinLineLength);
    ui->spnMaxLineGap->setValue(vMaxLineGap);
}

/*****************************************************************************
 *
 *****************************************************************************/
void FHoughLineDialog::on_cmdOk_clicked()
{
    vRho = ui->spnRho->value();
    vTheta = ui->spnTheta->value();
    vThresh = ui->spnThresh->value();
    vMinLineLength = ui->spnMinLineLength->value();
    vMaxLineGap = ui->spnMaxLineGap->value();
    close();
}

/*****************************************************************************
 *
 *****************************************************************************/
void FHoughLineDialog::on_cmdCancel_clicked()
{
    ui->spnRho->setValue(vRho);
    ui->spnTheta->setValue(vTheta);
    ui->spnThresh->setValue(vThresh);
    ui->spnMinLineLength->setValue(vMinLineLength);
    ui->spnMaxLineGap->setValue(vMaxLineGap);
    close();
}
