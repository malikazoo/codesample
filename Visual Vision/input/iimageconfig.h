/*****************************************************************************
 * Copyright Tim Price
 *****************************************************************************/

#ifndef IIMAGECONFIG_H
#define IIMAGECONFIG_H

#include <QDialog>

namespace Ui {
class IImageConfig;
}

/*****************************************************************************
 *
 *****************************************************************************/
class IImageConfig : public QDialog
{
    Q_OBJECT

    public:
        explicit IImageConfig(QWidget *parent = 0);
        ~IImageConfig();

        QString getFileName();
        bool getOkClicked();

        void setFileName(QString name);

    private slots:
        void on_cmdOk_clicked();
        void on_cmdCancel_clicked();

    private:
        Ui::IImageConfig *ui;
        bool vOkClicked;

};

#endif // IIMAGECONFIG_H
