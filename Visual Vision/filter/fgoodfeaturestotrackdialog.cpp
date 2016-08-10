#include "fgoodfeaturestotrackdialog.h"
#include "ui_fgoodfeaturestotrackdialog.h"

FGoodFeaturesToTrackDialog::FGoodFeaturesToTrackDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FGoodFeaturesToTrackDialog)
{
    ui->setupUi(this);
    maxCorners = 0;
    quality = 0;
    minDistance = 0;

    ui->spnMaxCorners->setValue(maxCorners);
    ui->spnMinDist->setValue(minDistance);
    ui->spnQuality->setValue(quality);

}

FGoodFeaturesToTrackDialog::~FGoodFeaturesToTrackDialog()
{
    delete ui;
}

int FGoodFeaturesToTrackDialog::getMaxCorners()
{
    return maxCorners;
}

double FGoodFeaturesToTrackDialog::getQuality()
{
    return quality;
}

double FGoodFeaturesToTrackDialog::getMinDistance()
{
    return minDistance;
}

void FGoodFeaturesToTrackDialog::setMaxCorners(int val)
{
    maxCorners = val;
}

void FGoodFeaturesToTrackDialog::setQuality(double val)
{
    quality = val;
}

void FGoodFeaturesToTrackDialog::setMinDistance(double val)
{
    minDistance = val;
}

void FGoodFeaturesToTrackDialog::on_cmdOk_clicked()
{
    maxCorners = ui->spnMaxCorners->value();
    quality = ui->spnQuality->value();
    minDistance = ui->spnMinDist->value();
    close();
}

void FGoodFeaturesToTrackDialog::on_cmdCancel_clicked()
{
    ui->spnMaxCorners->setValue(maxCorners);
    ui->spnQuality->setValue(quality);
    ui->spnMinDist->setValue(minDistance);
    close();
}
