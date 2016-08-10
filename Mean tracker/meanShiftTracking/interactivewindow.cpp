#include "interactivewindow.h"
#include <QtGui>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QFileDialog>
#include <QSlider>
#include <QMediaPlayer>
#include <QVBoxLayout>
#include <QGraphicsVideoItem>
#include <QGraphicsScene>
#include "interactivegraphicsview.h"
#include "interactivevideocontroller.h"


InteractiveWindow::InteractiveWindow(QWidget *parent) :
    QMainWindow(parent)
{
    mpOpenAction = new QAction(tr("&Open"), this);
    connect(mpOpenAction, SIGNAL(triggered()), this, SLOT(on_open_clicked()));
    mpProcessAction = new QAction(tr("&Process"), this);
    connect(mpProcessAction, SIGNAL(triggered()), this, SLOT(on_process_clicked()));

    mpFileMenu = new QMenu(tr("&File"), this);
    mpFileMenu->addAction(mpOpenAction);
    mpEditMenu = new QMenu(tr("&Edit"), this);
    mpEditMenu->addAction(mpProcessAction);

    mpPlayer = new QMediaPlayer(this);
    connect(mpPlayer, SIGNAL(durationChanged(qint64)), SLOT(durationChanged(qint64)));
    connect(mpPlayer, SIGNAL(positionChanged(qint64)), SLOT(positionChanged(qint64)));

    mpVideoView = new InteractiveGraphicsView(this);
    mpVideoScene = new QGraphicsScene(mpVideoView);
    mpVideoItem = new QGraphicsVideoItem();
    mpVideoView->setScene(mpVideoScene);
    mpVideoScene->addItem(mpVideoItem);
    mpPlayer->setVideoOutput(mpVideoItem);

    mpController = new InteractiveVideoController(this);
    connect(mpController, SIGNAL(play()), mpPlayer, SLOT(play()));
    connect(mpController, SIGNAL(pause()), mpPlayer, SLOT(pause()));
    connect(mpController, SIGNAL(stop()), mpPlayer, SLOT(stop()));
    connect(mpController, SIGNAL(stop()), mpVideoView, SLOT(update()));
    connect(mpPlayer, SIGNAL(stateChanged(QMediaPlayer::State)),
            mpController, SLOT(setState(QMediaPlayer::State)));

    mpController->setState(mpPlayer->state());


    this->menuBar()->addMenu(mpFileMenu);
    this->menuBar()->addMenu(mpEditMenu);

    this->setWindowTitle(tr("Interactive Window"));
    this->resize(200, 200);

    mpLayout = new QVBoxLayout(this);
    mpLayout->addWidget(mpVideoView);
    mpLayout->addWidget(mpController);
    mpCentralWidget = new QWidget(this);
    mpCentralWidget->setLayout(mpLayout);

    this->setCentralWidget(mpCentralWidget);

    vs = new VideoSurface();

    mpPlayer->setVideoOutput(vs);

    qDebug() << "UI Initalized";
}

InteractiveWindow::~InteractiveWindow()
{
    if(mpOpenAction)
    {
        delete mpOpenAction;
        mpOpenAction = NULL;
    }
    if(mpFileMenu)
    {
        delete mpFileMenu;
        mpFileMenu = NULL;
    }
    if(mpEditMenu)
    {
        delete mpEditMenu;
        mpEditMenu = NULL;
    }

    if (vs)
    {
        delete vs;
        vs = NULL;
    }
}

void InteractiveWindow::seek(int seconds)
{
    mpPlayer->setPosition(seconds * 1000);
}

void InteractiveWindow::on_open_clicked()
{
    mFilename = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::currentPath());
    if (!mFilename.isEmpty())
    {
        mpPlayer->setMedia(QUrl::fromLocalFile(mFilename));
        setWindowTitle(mFilename);
        mpPlayer->play();

    }
}

void InteractiveWindow::on_process_clicked()
{
    QPainter pnt;
    //mpVideoScene->render(pnt);
    QImage destination;


    //Mat img = Mat(img.rows, img.cols, format).clone();


}

void InteractiveWindow::durationChanged(qint64 duration)
{
    if(mpController)
    {
        mpController->setSliderDuration(duration / 1000);
    }
}

void InteractiveWindow::positionChanged(qint64 progress)
{
    if(mpController)
    {
        mpController->setSliderPosition(progress / 1000);
    }
}
