/*****************************************************************************
 * Copyright Tim Price
 *****************************************************************************/

#ifndef FDRAWPOINTSDIALOG_H
#define FDRAWPOINTSDIALOG_H

#include <QDialog>
#include <QColorDialog>

namespace Ui {
class FDrawPointsDialog;
}

class FDrawPointsDialog : public QDialog
{
        Q_OBJECT

    public:
        explicit FDrawPointsDialog(QWidget *parent = 0);
        ~FDrawPointsDialog();

        void setColor(QColor val);
        void setSize(float val);
        void setShape(QString shape);


    private slots:
        void on_cmdColorChoose_clicked();

    private:
        Ui::FDrawPointsDialog *ui;
        QColor vCol;
        QColor vTempCol;
        float vSize;
        int vShape;
};

#endif // FDRAWPOINTSDIALOG_H
