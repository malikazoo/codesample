#include "fdialatedialog.h"
#include "ui_fdialatedialog.h"

/*****************************************************************************
 *
 *****************************************************************************/
FDialateDialog::FDialateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FDialateDialog)
{
    ui->setupUi(this);
}

/*****************************************************************************
 *
 *****************************************************************************/
FDialateDialog::~FDialateDialog()
{
    delete ui;
}

/*****************************************************************************
 *
 *****************************************************************************/
FDialateDialog::DIALATETYPE FDialateDialog::getDialateType()
{
    return vType;
}

/*****************************************************************************
 *
 *****************************************************************************/
int FDialateDialog::getSizeX()
{
    return vSizeX;
}

/*****************************************************************************
 *
 *****************************************************************************/
int FDialateDialog::getSizeY()
{
    return vSizeY;
}

/*****************************************************************************
 *
 *****************************************************************************/
void FDialateDialog::setDialateType(FDialateDialog::DIALATETYPE type)
{
    vType = type;
}

/*****************************************************************************
 *
 *****************************************************************************/
void FDialateDialog::setSizeX(int val)
{
    vSizeX = val;
}

/*****************************************************************************
 *
 *****************************************************************************/
void FDialateDialog::setSizeY(int val)
{
    vSizeY = val;
}

/*****************************************************************************
 *
 *****************************************************************************/
void FDialateDialog::on_cmdOk_clicked()
{
    vType = getType(ui->cboType->currentIndex());
    vSizeX = ui->spnSizeX->value();
    vSizeY = ui->spnSizeY->value();
    close();
}

/*****************************************************************************
 *
 *****************************************************************************/
void FDialateDialog::on_cmdCancel_clicked()
{
    ui->cboType->setCurrentIndex(getType(vType));
    ui->spnSizeX->setValue(vSizeX);
    ui->spnSizeY->setValue(vSizeY);
    close();
}

/*****************************************************************************
 *
 *****************************************************************************/
FDialateDialog::DIALATETYPE FDialateDialog::getType(int type)
{
    DIALATETYPE t = RECTANGLE;
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
int FDialateDialog::getType(FDialateDialog::DIALATETYPE type)
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
