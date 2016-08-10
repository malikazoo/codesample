#include "fhoughcircledialog.h"
#include "ui_fhoughcircledialog.h"

/*****************************************************************************
 *
 *****************************************************************************/
FHoughCircleDialog::FHoughCircleDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FHoughCircleDialog)
{
    ui->setupUi(this);

    vMinDistance = 8;
    vParam1 = 200;
    vParam2 = 100;
    vMinRadius = 0;
    vMaxRadius = 0;
    ui->spnMinDist->setValue(vMinDistance);
    ui->spnUppEdges->setValue(vParam1);
    ui->spnTheshCenter->setValue(vParam2);
    ui->spnMinRadius->setValue(vMinRadius);
    ui->spnMaxRadius->setValue(vMaxRadius);
}

/*****************************************************************************
 *
 *****************************************************************************/
FHoughCircleDialog::~FHoughCircleDialog()
{
    delete ui;
}

/*****************************************************************************
 *
 *****************************************************************************/
double FHoughCircleDialog::param1()
{
    return vParam1;
}

/*****************************************************************************
 *
 *****************************************************************************/
double FHoughCircleDialog::param2()
{
    return vParam2;
}

/*****************************************************************************
 *
 *****************************************************************************/
int FHoughCircleDialog::minRadius()
{
    return vMinRadius;
}

/*****************************************************************************
 *
 *****************************************************************************/
int FHoughCircleDialog::maxRadius()
{
    return vMaxRadius;
}

/*****************************************************************************
 *
 *****************************************************************************/
int FHoughCircleDialog::minDistance()
{
    return vMinDistance;
}

/*****************************************************************************
 *
 *****************************************************************************/
void FHoughCircleDialog::setParam1(double val)
{
    vParam1 = val;
}

/*****************************************************************************
 *
 *****************************************************************************/
void FHoughCircleDialog::setParam2(double val)
{
    vParam2 = val;
}

/*****************************************************************************
 *
 *****************************************************************************/
void FHoughCircleDialog::setMinRadius(int val)
{
    vMinRadius = val;
}

/*****************************************************************************
 *
 *****************************************************************************/
void FHoughCircleDialog::setMaxRadius(int val)
{
    vMaxRadius = val;
}

/*****************************************************************************
 *
 *****************************************************************************/
void FHoughCircleDialog::setMinDistance(int val)
{
    vMinDistance = val;
}

/*****************************************************************************
 *
 *****************************************************************************/
void FHoughCircleDialog::on_cmdOk_clicked()
{
    vMinDistance = ui->spnMinDist->value();
    vParam1 = ui->spnUppEdges->value();
    vParam2 = ui->spnTheshCenter->value();
    vMinRadius = ui->spnMinRadius->value();
    vMaxRadius = ui->spnMaxRadius->value();
    close();
}

/*****************************************************************************
 *
 *****************************************************************************/
void FHoughCircleDialog::on_cmdCancel_clicked()
{
    ui->spnMinDist->setValue(vMinDistance);
    ui->spnUppEdges->setValue(vParam1);
    ui->spnTheshCenter->setValue(vParam2);
    ui->spnMinRadius->setValue(vMinRadius);
    ui->spnMaxRadius->setValue(vMaxRadius);
    close();
}
