/*****************************************************************************
 * Copyright Tim Price
 *****************************************************************************/

#ifndef FGOODFEATURESTOTRACKDIALOG_H
#define FGOODFEATURESTOTRACKDIALOG_H

#include <QDialog>

namespace Ui {
class FGoodFeaturesToTrackDialog;
}

class FGoodFeaturesToTrackDialog : public QDialog
{
        Q_OBJECT

    public:
        explicit FGoodFeaturesToTrackDialog(QWidget *parent = 0);
        ~FGoodFeaturesToTrackDialog();

        int getMaxCorners();
        double getQuality();
        double getMinDistance();

        void setMaxCorners(int val);
        void setQuality(double val);
        void setMinDistance(double val);


    private slots:
        void on_cmdOk_clicked();

        void on_cmdCancel_clicked();



    private:
        Ui::FGoodFeaturesToTrackDialog *ui;

        int maxCorners;
        double quality;
        double minDistance;

};

#endif // FGOODFEATURESTOTRACKDIALOG_H
