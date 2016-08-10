#include "fdrawpointsdialog.h"
#include "ui_fdrawpointsdialog.h"

FDrawPointsDialog::FDrawPointsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FDrawPointsDialog)
{
    ui->setupUi(this);
    vTempCol = vCol;
}

FDrawPointsDialog::~FDrawPointsDialog()
{
    delete ui;
}

void FDrawPointsDialog::on_cmdColorChoose_clicked()
{
   vTempCol = QColorDialog::getColor(vTempCol);

}
