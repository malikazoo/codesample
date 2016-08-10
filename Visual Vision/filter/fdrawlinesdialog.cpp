#include "fdrawlinesdialog.h"
#include "ui_fdrawlinesdialog.h"

/*****************************************************************************
 *
 *****************************************************************************/
FDrawLinesDialog::FDrawLinesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FDrawLinesDialog)
{
    ui->setupUi(this);
    vWidth = 1;
    vCol = QColor(0,0,0);
}

/*****************************************************************************
 *
 *****************************************************************************/
FDrawLinesDialog::~FDrawLinesDialog()
{
    delete ui;
}

/*****************************************************************************
 *
 *****************************************************************************/
QColor FDrawLinesDialog::getSelectedColor()
{
    return vCol;
}

/*****************************************************************************
 *
 *****************************************************************************/
int FDrawLinesDialog::getWidth()
{
    return vWidth;
}

/*****************************************************************************
 *
 *****************************************************************************/
void FDrawLinesDialog::setColor(QColor col)
{
    vCol = col;
}

/*****************************************************************************
 *
 *****************************************************************************/
void FDrawLinesDialog::setWidth(int width)
{
    vWidth = width;
}

/*****************************************************************************
 *
 *****************************************************************************/
void FDrawLinesDialog::on_cmdOk_clicked()
{
    vWidth = ui->spnWidth->value();

    close();
}

/*****************************************************************************
 *
 *****************************************************************************/
void FDrawLinesDialog::on_cmdCancel_clicked()
{
    ui->spnWidth->setValue(vWidth);
    close();
}

/*****************************************************************************
 *
 *****************************************************************************/
void FDrawLinesDialog::on_cmdColor_clicked()
{
    vCol = QColorDialog::getColor(vCol);
    ui->frmColor->setPalette(QPalette(backgroundRole(), vCol));
}
