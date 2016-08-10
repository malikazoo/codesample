#include "filebrowser.h"

/*****************************************************************************
 *
 *****************************************************************************/
Filebrowser::Filebrowser(QWidget *parent) :
    QWidget(parent)
{
    this->setLayout(&hbx);
    hbx.setSpacing(0);
    hbx.setMargin(0);

    hbx.addWidget(&te);
    hbx.addWidget(&cmdBrowse);

    cmdBrowse.setText("Browse");

    connect(&cmdBrowse, SIGNAL(clicked()), this, SLOT(btnClicked()));
    vType = OPENFILE;
}

/*****************************************************************************
 *
 *****************************************************************************/
void Filebrowser::setType(Filebrowser::FILETYPE type)
{
    vType = type;
}

/*****************************************************************************
 *
 *****************************************************************************/
QString Filebrowser::getFileName()
{
    return filename;
}

/*****************************************************************************
 *
 *****************************************************************************/
void Filebrowser::setFileName(QString name)
{
    filename = name;
    te.setText(filename);
}

/*****************************************************************************
 *
 *****************************************************************************/
void Filebrowser::btnClicked()
{
    QFileDialog fil;

    if (vType == OPENFILE)
        filename = fil.getOpenFileName();
    else
        filename = fil.getSaveFileName();

    te.setText(filename);

}
