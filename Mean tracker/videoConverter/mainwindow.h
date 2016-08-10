#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QFileDialog>
#include <QFile>
#include <QDir>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;


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
        void on_cmdLoad_clicked();
        void on_cmdRun_clicked();

        void on_cmdCalib_clicked();

        void on_chkDistort_clicked();

    private:
        Ui::MainWindow *ui;
        QString selectedFile;
        QString calibFile;


        int frame_count;

};

#endif // MAINWINDOW_H
