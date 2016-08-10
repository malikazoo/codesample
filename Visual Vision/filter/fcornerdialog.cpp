#include "fcornerdialog.h"
#include "ui_fcornerdialog.h"

FCornerDialog::FCornerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FCornerDialog)
{
    ui->setupUi(this);
}

FCornerDialog::~FCornerDialog()
{
    delete ui;
}
