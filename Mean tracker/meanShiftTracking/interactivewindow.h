#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVideoFrame>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

#include "videosurface.h"

class QAction;
class QMenu;
class QSlider;
class InteractiveGraphicsView;
class QMediaPlayer;
class InteractiveVideoController;
class QVBoxLayout;
class QGraphicsScene;
class QGraphicsVideoItem;

class InteractiveWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit InteractiveWindow(QWidget *parent = 0);
    ~InteractiveWindow();


private slots:
    void on_open_clicked();
    void on_process_clicked();

    void seek(int seconds);
    void durationChanged(qint64 duration);
    void positionChanged(qint64 progress);

private:
    QAction * mpOpenAction;
    QAction * mpProcessAction;

    QMenu * mpFileMenu;
    QMenu * mpEditMenu;

    QString mFilename;

    QMediaPlayer * mpPlayer;
    InteractiveGraphicsView * mpVideoView;
    QGraphicsVideoItem * mpVideoItem;
    QGraphicsScene * mpVideoScene;
    InteractiveVideoController * mpController;

    QWidget * mpCentralWidget;
    QVBoxLayout * mpLayout;

    VideoSurface* vs;


};

#endif // MAINWINDOW_H
