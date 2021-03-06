#include "fthresholddialog.h"
#include "ui_fthresholddialog.h"

/*****************************************************************************
 *
 *****************************************************************************/
FThresholdDialog::FThresholdDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FThresholdDialog)
{
    ui->setupUi(this);
    vValue = 127;
    vType = 0;
}

/*****************************************************************************
 *
 *****************************************************************************/
FThresholdDialog::~FThresholdDialog()
{
    delete ui;
}

/*****************************************************************************
 *
 *****************************************************************************/
int FThresholdDialog::getType()
{
    return vType;
}

/*****************************************************************************
 *
 *****************************************************************************/
int FThresholdDialog::getValue()
{
    return vValue;
}

/*****************************************************************************
 *
 *****************************************************************************/
void FThresholdDialog::setType(int val)
{
    vType = val;
}

/*****************************************************************************
 *
 *****************************************************************************/
void FThresholdDialog::setValue(int val)
{
    vValue = val;
}

/*****************************************************************************
 *
 *****************************************************************************/
void FThresholdDialog::showEvent(QShowEvent*)
{
    ui->cboType->setCurrentIndex(vType);
    ui->spnValue->setValue(vValue);
}

/*****************************************************************************
 *
 *****************************************************************************/
void FThresholdDialog::on_cmdOk_clicked()
{
    vType = ui->cboType->currentIndex();
    vValue = ui->spnValue->value();

    close();
}

/*****************************************************************************
 *
 *****************************************************************************/
void FThresholdDialog::on_cmdCancel_clicked()
{
    ui->cboType->setCurrentIndex(vType);
    ui->spnValue->setValue(vValue);

    close();
}
