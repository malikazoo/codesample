#include "fcannydialog.h"
#include "ui_fcannydialog.h"

/*****************************************************************************
 *
 *****************************************************************************/
FCannyDialog::FCannyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FCannyDialog)
{
    ui->setupUi(this);

    kernel = 3;
    thresh1 = 100;
    thresh2 = 200;

    ui->spnKernelSize->setValue(kernel);
    ui->spnThresh1->setValue(thresh1);
    ui->spnThresh2->setValue(thresh2);
}

/*****************************************************************************
 *
 *****************************************************************************/
FCannyDialog::~FCannyDialog()
{
    delete ui;
}

/*****************************************************************************
 *
 *****************************************************************************/
double FCannyDialog::getThresh1()
{
    return thresh1;
}

/*****************************************************************************
 *
 *****************************************************************************/
double FCannyDialog::getThresh2()
{
    return thresh2;
}

/*****************************************************************************
 *
 *****************************************************************************/
int FCannyDialog::getKernelSize()
{
    return kernel;
}

/*****************************************************************************
 * Sets the first threshold
 *****************************************************************************/
void FCannyDialog::setThresh1(double val)
{
    thresh1 = val;
}

/*****************************************************************************
 * Sets the second threshold
 *****************************************************************************/
void FCannyDialog::setThresh2(double val)
{
    thresh2 = val;
}

/*****************************************************************************
 * Sets the kernel size
 *****************************************************************************/
void FCannyDialog::setKernelSize(int val)
{
    kernel = val;
}

/*****************************************************************************
 *
 *****************************************************************************/
void FCannyDialog::showEvent(QShowEvent*)
{
    ui->spnKernelSize->setValue(kernel);
    ui->spnThresh1->setValue(thresh1);
    ui->spnThresh2->setValue(thresh2);
}

/*****************************************************************************
 *
 *****************************************************************************/
void FCannyDialog::on_cmdOk_clicked()
{
    kernel = ui->spnKernelSize->value();
    thresh1 = ui->spnThresh1->value();
    thresh2 = ui->spnThresh2->value();
    close();
}

/*****************************************************************************
 *
 *****************************************************************************/
void FCannyDialog::on_cmdCancel_clicked()
{
    ui->spnKernelSize->setValue(kernel);
    ui->spnThresh1->setValue(thresh1);
    ui->spnThresh2->setValue(thresh2);
    close();
}
