#include "oscreenconfig.h"
#include "ui_oscreenconfig.h"

/*****************************************************************************
 *
 *****************************************************************************/
OScreenConfig::OScreenConfig(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OScreenConfig)
{
    ui->setupUi(this);
}

/*****************************************************************************
 *
 *****************************************************************************/
OScreenConfig::~OScreenConfig()
{
    delete ui;
}
