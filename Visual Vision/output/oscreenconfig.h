/*****************************************************************************
 * Copyright Tim Price
 *****************************************************************************/

#ifndef OSCREENCONFIG_H
#define OSCREENCONFIG_H

#include <QDialog>

namespace Ui {
class OScreenConfig;
}

/*****************************************************************************
 *
 *****************************************************************************/
class OScreenConfig : public QDialog
{
    Q_OBJECT

public:
    explicit OScreenConfig(QWidget *parent = 0);
    ~OScreenConfig();

private:
    Ui::OScreenConfig *ui;
};

#endif // OSCREENCONFIG_H
