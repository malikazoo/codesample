/*****************************************************************************
 * Copyright Tim Price
 *****************************************************************************/

#ifndef IVIDEOCONFIG_H
#define IVIDEOCONFIG_H

#include <QDialog>

namespace Ui {
class IVideoConfig;
}

/*****************************************************************************
 *
 *****************************************************************************/
class IVideoConfig : public QDialog
{
    Q_OBJECT

    public:
        explicit IVideoConfig(QWidget *parent = 0);
        ~IVideoConfig();

        QString getFileName();
        bool OkClicked();

        void setFileName(QString val);

private slots:
        void on_cmdOk_clicked();
        void on_cmdCancel_clicked();

private:
        Ui::IVideoConfig *ui;
        bool vOkClicked;
};

#endif // IVIDEOCONFIG_H
