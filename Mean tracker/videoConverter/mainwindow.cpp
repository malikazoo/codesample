#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_cmdLoad_clicked()
{
    QFileDialog diag;
    diag.exec();

    selectedFile = diag.selectedFiles().at(0);
    ui->txtFile->setText(selectedFile);

    VideoCapture vid(selectedFile.toStdString().c_str());
    frame_count = vid.get(CV_CAP_PROP_FRAME_COUNT);
    ui->lblCount->setText("Video count: " + QString::number(frame_count));

}

void MainWindow::on_cmdRun_clicked()
{
    if (selectedFile != "")
    {
        VideoCapture vid(selectedFile.toStdString().c_str());

        VideoWriter vout;

        vout.open((selectedFile + "out.mpeg").toStdString().c_str(),CV_FOURCC('M','P','E','G'),30,Size(vid.get(CV_CAP_PROP_FRAME_WIDTH), vid.get(CV_CAP_PROP_FRAME_HEIGHT)));

        qDebug() << "Frame cnt " << frame_count;

        QFileInfo filedir = QFileInfo(selectedFile);
        QDir currdir = filedir.dir();

        int sample_size = frame_count;
        if (sample_size <= 0)
            return;

        int sample_interval = frame_count / sample_size;
        int sample_cnt = 0;
        ui->prog->setMaximum(frame_count);

        bool undistorted = ui->chkDistort->isChecked();
        Mat cammatrix;
        Mat distortion;
        double rms;
        if (undistorted)
        {
            FileStorage file(calibFile.toStdString().c_str(),FileStorage::READ);
            file["rms"] >> rms;
            file["cameramatrix"] >> cammatrix;
            file["distortion"] >> distortion;
        }

        for (int i = 0; i < frame_count; i++)
        {
            Mat r;
            vid >> r;
            QString writepath = selectedFile + "-" + QString::number(i) + ".png";

            Mat c;

            if (undistorted)
            {
                undistort(r, c, cammatrix, distortion);
            }
            else
            {
                c = r;
            }

            imwrite(writepath.toStdString().c_str(), c);
            vout << c;
            ui->prog->setValue(i);
        }

        ui->prog->setValue(frame_count);
    }

}

void MainWindow::on_cmdCalib_clicked()
{
    QFileDialog diag;
    diag.exec();

    calibFile = diag.selectedFiles().at(0);
    ui->txtCalib->setText(calibFile);
}

void MainWindow::on_chkDistort_clicked()
{

}
