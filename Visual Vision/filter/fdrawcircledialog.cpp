#include "fdrawcircledialog.h"
#include "ui_fdrawcircledialog.h"

/*****************************************************************************
 *
 *****************************************************************************/
FDrawCircleDialog::FDrawCircleDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FDrawCircleDialog)
{
    ui->setupUi(this);

    vCol = Qt::black;
    ui->frmShowColor->setPalette(QPalette(backgroundRole(), vCol));
    //ui->frmShowColor->setBackgroundRole(QPalette(backgroundRole(),col));
    ui->frmShowColor->autoFillBackground();
    vWidth = 1;
}

/*****************************************************************************
 *
 *****************************************************************************/
FDrawCircleDialog::~FDrawCircleDialog()
{
    delete ui;
}

/*****************************************************************************
 * Returns the color of the circles
 *****************************************************************************/
QColor FDrawCircleDialog::getColor()
{
    return vCol;
}

/*****************************************************************************
 * Returns the width of the circles
 *****************************************************************************/
int FDrawCircleDialog::getWidth()
{
    return vWidth;
}

/*****************************************************************************
 * Sets the color of the circles being drawn
 *****************************************************************************/
void FDrawCircleDialog::setColor(QColor col)
{
    vCol = col;
}

/*****************************************************************************
 * Sets the width of the circles being drawn
 *****************************************************************************/
void FDrawCircleDialog::setWidth(int width)
{
    vWidth = width;
}

/*****************************************************************************
 * User has clicked on change color button
 *****************************************************************************/
void FDrawCircleDialog::on_cmdColor_clicked()
{
    vCol = QColorDialog::getColor(vCol);
    ui->frmShowColor->setPalette(QPalette(backgroundRole(), vCol));
}

/*****************************************************************************
 * User has clicked OK to accept the changes made
 *****************************************************************************/
void FDrawCircleDialog::on_cmdOk_clicked()
{
    vWidth = ui->spnWidth->value();
    close();
}

/*****************************************************************************
 * User has canceled the changes if any made
 *****************************************************************************/
void FDrawCircleDialog::on_cmdCancel_clicked()
{
    ui->spnWidth->setValue(vWidth);
    close();
}

