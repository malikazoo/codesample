/*****************************************************************************
 * Copyright Tim Price
 *****************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QDebug>
#include <QListWidgetItem>
#include <QPushButton>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QFileDialog>

#include "filter/filter.h"
#include "filtermap.h"
#include "filterregister.h"
#include "filterfactory.h"
#include "inputfactorybase.h"
#include "outputfactorybase.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

    private slots:
        void update();

        void on_cmdPlay_clicked();

        void on_hslPlay_sliderMoved(int position);



        void on_hslPlay_sliderReleased();

        void on_actionOpen_triggered();

        void on_actionSave_triggered();

    private:
        Ui::MainWindow *ui;
        FilterMap* map;

        FilterRegister* registry;
        bool currPlay;
        void run();

        void saveFile(QString filename);
        void loadFile(QString filename);

};

#endif // MAINWINDOW_H
