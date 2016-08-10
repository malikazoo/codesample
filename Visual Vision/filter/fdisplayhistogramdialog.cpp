#include "fdisplayhistogramdialog.h"
#include "ui_fdisplayhistogramdialog.h"

/*****************************************************************************
 *
 *****************************************************************************/
FDisplayHistogramDialog::FDisplayHistogramDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FDisplayHistogramDialog)
{
    ui->setupUi(this);
    vWidth = 512;
    vHeight = 100;

    ui->spnHeight->setValue(vHeight);
    ui->spnWidth->setValue(vWidth);

    vTempBack = vBack = QColor(Qt::white);
    vTempFore = vFore = QColor(Qt::black);

    ui->frmBackColor->setPalette(QPalette(backgroundRole(), vTempBack));
    ui->frmForeColor->setPalette(QPalette(backgroundRole(), vTempFore));

}

/*****************************************************************************
 *
 *****************************************************************************/
FDisplayHistogramDialog::~FDisplayHistogramDialog()
{
    delete ui;
}

/*****************************************************************************
 *
 *****************************************************************************/
int FDisplayHistogramDialog::getWidth()
{
    return vWidth;
}

/*****************************************************************************
 *
 *****************************************************************************/
int FDisplayHistogramDialog::getHeight()
{
    return vHeight;
}

/*****************************************************************************
 *
 *****************************************************************************/
QColor FDisplayHistogramDialog::getForeColor()
{
    return vFore;
}

/*****************************************************************************
 *
 *****************************************************************************/
QColor FDisplayHistogramDialog::getBackColor()
{
    return vBack;
}

/*****************************************************************************
 *
 *****************************************************************************/
void FDisplayHistogramDialog::setWidth(int val)
{
    vWidth = val;
}

/*****************************************************************************
 *
 *****************************************************************************/
void FDisplayHistogramDialog::setHeight(int val)
{
    vHeight = val;
}

/*****************************************************************************
 *
 *****************************************************************************/
void FDisplayHistogramDialog::setForeColor(QColor col)
{
    vFore = col;
}

/*****************************************************************************
 *
 *****************************************************************************/
void FDisplayHistogramDialog::setBackColor(QColor col)
{
    vBack = col;
}

/*****************************************************************************
 *
 *****************************************************************************/
void FDisplayHistogramDialog::showEvent(QShowEvent*)
{
    ui->spnHeight->setValue(vHeight);
    ui->spnWidth->setValue(vWidth);
    vTempBack = vBack;
    vTempFore = vFore;
    ui->frmBackColor->setPalette(QPalette(backgroundRole(), vTempBack));
    ui->frmForeColor->setPalette(QPalette(backgroundRole(), vTempFore));
}

/*****************************************************************************
 *
 *****************************************************************************/
void FDisplayHistogramDialog::on_cmdOk_clicked()
{
    vWidth = ui->spnWidth->value();
    vHeight = ui->spnHeight->value();
    vBack = vTempBack;
    vFore = vTempFore;
    close();
}

/*****************************************************************************
 *
 *****************************************************************************/
void FDisplayHistogramDialog::on_cmdCancel_clicked()
{
    ui->spnHeight->setValue(vHeight);
    ui->spnWidth->setValue(vWidth);
    vTempBack = vBack;
    vTempFore = vFore;
    ui->frmBackColor->setPalette(QPalette(backgroundRole(), vTempBack));
    ui->frmForeColor->setPalette(QPalette(backgroundRole(), vTempFore));

    close();
}

/*****************************************************************************
 *
 *****************************************************************************/
void FDisplayHistogramDialog::on_cmdBackColor_clicked()
{
    vTempBack = QColorDialog::getColor(vTempBack);
    ui->frmBackColor->setPalette(QPalette(backgroundRole(), vTempBack));

}

/*****************************************************************************
 *
 *****************************************************************************/
void FDisplayHistogramDialog::on_cmdForeColor_clicked()
{
    vTempFore = QColorDialog::getColor(vTempFore);
    ui->frmForeColor->setPalette(QPalette(backgroundRole(), vTempFore));
}
