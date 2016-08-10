/*****************************************************************************
 * Copyright Tim Price
 *****************************************************************************/

#ifndef FILEBROWSER_H
#define FILEBROWSER_H

#include <QWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QLineEdit>

/*****************************************************************************
 *
 *****************************************************************************/
class Filebrowser : public QWidget
{
    Q_OBJECT
    public:
        explicit Filebrowser(QWidget *parent = 0);
        enum FILETYPE { SAVEFILE, OPENFILE };

        void setType(FILETYPE type);

        QString getFileName();
        void setFileName(QString name);

    signals:

    public slots:

    private slots:
        void btnClicked();

    private:
        QLineEdit te;
        QPushButton cmdBrowse;
        QHBoxLayout hbx;

        FILETYPE vType;
        QString filename;

};

#endif // FILEBROWSER_H
