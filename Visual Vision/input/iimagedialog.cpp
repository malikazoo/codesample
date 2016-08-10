#include "iimagedialog.h"
#include "ui_iimagedialog.h"

IImageDialog::IImageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IImageDialog)
{
    ui->setupUi(this);
}

IImageDialog::~IImageDialog()
{
    delete ui;
}
