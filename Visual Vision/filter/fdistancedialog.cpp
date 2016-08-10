#include "fdistancedialog.h"
#include "ui_fdistancedialog.h"

/*****************************************************************************
 *
 *****************************************************************************/
FDistanceDialog::FDistanceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FDistanceDialog)
{
    ui->setupUi(this);
    vType = DIST_EUCLIDEAN;
    ui->cboType->setCurrentIndex(0);
}

/*****************************************************************************
 *
 *****************************************************************************/
FDistanceDialog::~FDistanceDialog()
{
    delete ui;
}

/*****************************************************************************
 *
 *****************************************************************************/
FDistanceDialog::FDISTANCE FDistanceDialog::getType()
{
    return vType;
}

/*****************************************************************************
 *
 *****************************************************************************/
void FDistanceDialog::showEvent(QShowEvent*)
{
    switch (vType)
    {
        case DIST_EUCLIDEAN:
            ui->cboType->setCurrentIndex(0);
            break;
        case DIST_MANHATTAN:
            ui->cboType->setCurrentIndex(1);
            break;
        case DIST_CHEBYSHEV:
            ui->cboType->setCurrentIndex(2);
            break;
    }

}

void FDistanceDialog::setType(FDistanceDialog::FDISTANCE type)
{
    vType = type;
}

/*****************************************************************************
 *
 *****************************************************************************/
void FDistanceDialog::on_cmdOk_clicked()
{
    switch (ui->cboType->currentIndex())
    {
        case 0:
            vType = DIST_EUCLIDEAN;
            break;
        case 1:
            vType = DIST_MANHATTAN;
            break;
        case 2:
            vType = DIST_CHEBYSHEV;
            break;
    }
    close();
}

/*****************************************************************************
 *
 *****************************************************************************/
void FDistanceDialog::on_cmdCancel_clicked()
{
    switch (vType)
    {
        case DIST_EUCLIDEAN:
            ui->cboType->setCurrentIndex(0);
            break;
        case DIST_MANHATTAN:
            ui->cboType->setCurrentIndex(1);
            break;
        case DIST_CHEBYSHEV:
            ui->cboType->setCurrentIndex(2);
            break;
    }

    close();
}
