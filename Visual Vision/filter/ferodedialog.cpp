#include "ferodedialog.h"
#include "ui_ferodedialog.h"

/*****************************************************************************
 *
 *****************************************************************************/
FErodeDialog::FErodeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FErodeDialog)
{
    ui->setupUi(this);
}

/*****************************************************************************
 *
 *****************************************************************************/
FErodeDialog::~FErodeDialog()
{
    delete ui;
}

/*****************************************************************************
 *
 *****************************************************************************/
FErodeDialog::ERODETYPE FErodeDialog::getErodeType()
{
    return vType;
}

/*****************************************************************************
 *
 *****************************************************************************/
int FErodeDialog::getSizeX()
{
    return sizeX;
}

/*****************************************************************************
 *
 *****************************************************************************/
int FErodeDialog::getSizeY()
{
    return sizeY;
}

/*****************************************************************************
 *
 *****************************************************************************/
void FErodeDialog::setErodeType(FErodeDialog::ERODETYPE type)
{
    vType = type;
}

/*****************************************************************************
 *
 *****************************************************************************/
void FErodeDialog::setSizeX(int val)
{
    sizeX = val;
}

/*****************************************************************************
 *
 *****************************************************************************/
void FErodeDialog::setSizeY(int val)
{
    sizeY = val;
}

/*****************************************************************************
 *
 *****************************************************************************/
void FErodeDialog::on_cmdOk_clicked()
{
    vType = getType(ui->cboType->currentIndex());
    sizeX = ui->spnSizeX->value();
    sizeY = ui->spnSizeY->value();
    close();
}

/*****************************************************************************
 *
 *****************************************************************************/
void FErodeDialog::on_cmdCancel_clicked()
{
    ui->cboType->setCurrentIndex(getType(vType));
    ui->spnSizeX->setValue(sizeX);
    ui->spnSizeY->setValue(sizeY);
    close();
}

/*****************************************************************************
 *
 *****************************************************************************/
FErodeDialog::ERODETYPE FErodeDialog::getType(int type)
{
    ERODETYPE t = RECTANGLE;
    switch(type)
    {
        case 0:
            t = RECTANGLE;
            break;
        case 1:
            t = CROSS;
            break;
        case 2:
            t = ELLIPSE;
            break;
    }
    return t;
}

/*****************************************************************************
 *
 *****************************************************************************/
int FErodeDialog::getType(FErodeDialog::ERODETYPE type)
{
    int t = 0;
    switch(type)
    {
        case RECTANGLE:
            t = 0;
            break;
        case CROSS:
            t = 1;
            break;
        case ELLIPSE:
            t = 2;
            break;
    }
    return t;
}
