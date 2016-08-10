#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QTimer>
#include "videoreader.h"
#include "meanshifttracker.h"

#include <QFile>
#include <QTextStream>

#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/calib3d/calib3d.hpp"
using namespace cv;

#define STR_SELECT_OBJ    "Select Object"
#define STR_FINISH_SELECT "Finish Selection"
#define TIMER_LENGTH 30


namespace Ui {
class MainWindow;
}

/*****************************************************************************
 * The state of the program, whether images have been loaded, rectangle
 * and tracking
 *****************************************************************************/
enum MainWindowStatus
{
    IMAGE_NOT_LOADED = 0,
    NORMAL,
    RECT_DRAWING,
    TRACKING
};

/*****************************************************************************
 *
 *****************************************************************************/
class MainWindow : public QMainWindow
{
        Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

    private slots:
        void on_cmdLoad_clicked();
        void on_cmdPlay_clicked();
        void on_btnNextFrame_clicked();
        void on_btnCmdSelect_clicked();
        void timerupdate();

protected:
        virtual void resizeEvent(QResizeEvent *event);
        virtual void paintEvent(QPaintEvent* e);

    private:
        Ui::MainWindow *ui;
        videoreader vids;
        MainWindowStatus mMainWindowStatus;
        QGraphicsPixmapItem* picture[4];
        QGraphicsScene* scene[4];

        QVector<Mat> mReferenceFrames;
        QVector<Mat> mCurrentFrames;
        cv::Rect mReferenceRect[4];
        cv::Rect mCandidateRect[4];

        MeanShiftTracker * mpMST[4];

        QTimer* timer;                      //Timer that loads the next frame and shows it
        bool timerrunning;                  //Whether the timer is running or not

        QPixmap fromMat(Mat img);           //Converts from Mat to pixmap for displaying
        void resize();
        void getNextFrame();

        QFile * mpFile[4];
        QTextStream * mpTextStream[4];
};

#endif // MAINWINDOW_H
