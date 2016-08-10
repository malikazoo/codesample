#include "fcolordialog.h"
#include "ui_fcolordialog.h"

/*****************************************************************************
 *
 *****************************************************************************/
FColorDialog::FColorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FColorDialog)
{
    ui->setupUi(this);

    red = 100;
    green = 100;
    blue = 100;

    ui->dblRed->setValue(100);
    ui->dblGreen->setValue(100);
    ui->dblBlue->setValue(100);

    ui->sldRed->setValue(100);
    ui->sldGreen->setValue(100);
    ui->sldBlue->setValue(100);
}

/*****************************************************************************
 *
 *****************************************************************************/
FColorDialog::~FColorDialog()
{
    delete ui;
}

/*****************************************************************************
 *
 *****************************************************************************/
double FColorDialog::amountRed()
{
    return ui->dblRed->value();
}

/*****************************************************************************
 *
 *****************************************************************************/
double FColorDialog::amountGreen()
{
    return ui->dblGreen->value();
}

/*****************************************************************************
 *
 *****************************************************************************/
double FColorDialog::amountBlue()
{
    return ui->dblBlue->value();
}

/*****************************************************************************
 *
 *****************************************************************************/
void FColorDialog::setRed(double val)
{
    red = val;
    ui->dblRed->setValue(val);
    ui->sldRed->setValue(val);
}

/*****************************************************************************
 *
 *****************************************************************************/
void FColorDialog::setGreen(double val)
{
    green = val;
    ui->dblGreen->setValue(val);
    ui->sldGreen->setValue(val);

}

/*****************************************************************************
 *
 *****************************************************************************/
void FColorDialog::setBlue(double val)
{
    blue = val;
    ui->dblBlue->setValue(val);
    ui->sldBlue->setValue(val);
}

/*****************************************************************************
 *
 *****************************************************************************/
void FColorDialog::on_cmdOk_clicked()
{
    red = ui->dblRed->value();
    green = ui->dblGreen->value();
    blue = ui->dblBlue->value();

    close();
}

/*****************************************************************************
 *
 *****************************************************************************/
void FColorDialog::on_cmdCancel_clicked()
{
    ui->dblBlue->setValue(blue);
    ui->sldBlue->setValue(blue);
    ui->dblGreen->setValue(green);
    ui->sldGreen->setValue(green);
    ui->dblRed->setValue(red);
    ui->sldRed->setValue(red);

    close();
}

/*****************************************************************************
 *
 *****************************************************************************/
void FColorDialog::on_sldRed_sliderMoved(int position)
{
    ui->dblRed->setValue(position);
}

/*****************************************************************************
 *
 *****************************************************************************/
void FColorDialog::on_sldGreen_sliderMoved(int position)
{
    ui->dblGreen->setValue(position);
}

/*****************************************************************************
 *
 *****************************************************************************/
void FColorDialog::on_sldBlue_sliderMoved(int position)
{
    ui->dblBlue->setValue(position);
}

/*****************************************************************************
 *
 *****************************************************************************/
void FColorDialog::on_dblRed_editingFinished()
{
    ui->sldRed->setValue(ui->dblRed->value());
}

/*****************************************************************************
 *
 *****************************************************************************/
void FColorDialog::on_dblGreen_editingFinished()
{
    ui->sldGreen->setValue(ui->dblGreen->value());
}

/*****************************************************************************
 *
 *****************************************************************************/
void FColorDialog::on_dblBlue_editingFinished()
{
    ui->sldBlue->setValue(ui->dblBlue->value());
}
