#include "mainwindow.h"
#include "ui_mainwindow.h"


/*****************************************************************************
 *
 *****************************************************************************/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    for (int i = 0; i < 4; i++)
    {
        scene[i] = new QGraphicsScene();
        picture[i] = new QGraphicsPixmapItem();
    }

    ui->gphPic1->setScene(scene[0]);
    ui->gphPic2->setScene(scene[1]);
    ui->gphPic3->setScene(scene[2]);
    ui->gphPic4->setScene(scene[3]);

    for (int i = 0; i < 4; i++)
    {
        scene[i]->addItem(picture[i]);
    }

    //Turn off the scroll bars so they don't interfere with the
    ui->gphPic1->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->gphPic1->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->gphPic2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->gphPic2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->gphPic3->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->gphPic3->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->gphPic4->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->gphPic4->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    mMainWindowStatus = IMAGE_NOT_LOADED;
    for(int i=0;i<4;i++)
    {
        mpMST[i] = new MeanShiftTracker();
    }

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerupdate()));
    timerrunning = false;

    for(int i=0;i<4;i++)
    {
        QString filename = "data_log-";
        filename += QString::number(i);
        filename += ".txt";
        mpFile[i] = new QFile(filename);
        mpFile[i]->open(QIODevice::WriteOnly | QIODevice::Text);
        mpTextStream[i] = new QTextStream(mpFile[i]);
    }

}

/*****************************************************************************
 *
 *****************************************************************************/
MainWindow::~MainWindow()
{
    delete ui;
    for(int i=0;i<4;i++)
    {
        delete mpMST[i];
        mpMST[i] = NULL;
    }
}


/*****************************************************************************
 * Called when the main window gets resized.  Calls resize to resize the
 * pictures
 *****************************************************************************/
void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);

    resize();
}

/*****************************************************************************
 * Converts from Mat to QPixmap
 *****************************************************************************/
QPixmap MainWindow::fromMat(Mat img)
{
    if (img.type() == CV_8UC3)
    {
        QImage image(img.data,img.cols,img.rows,img.step, QImage::Format_RGB888);
        return QPixmap::fromImage(image.rgbSwapped());
    }

    return QPixmap();
}

/*****************************************************************************
 * Resizes the pictures inside the frames.
 *****************************************************************************/
void MainWindow::resize()
{
    //If images have been loaded, then resize them to match the frames
    if (mMainWindowStatus != IMAGE_NOT_LOADED)
    {
        double height = vids.getHeight();
        double width = vids.getWidth();

        double uiheight = ui->gphPic1->height()-2;
        double uiwidth = ui->gphPic1->width()-2;

        double scaleh = uiheight / height;
        double scalew = uiwidth / width;

        double scale = ((scaleh > scalew) ? scalew : scaleh);

        for (int i = 0; i < 4; i++)
        {
            picture[i]->setScale(scale);
        }

        ui->gphPic1->setMaximumHeight(height*scale);
        ui->gphPic2->setMaximumHeight(height*scale);
        ui->gphPic3->setMaximumHeight(height*scale);
        ui->gphPic4->setMaximumHeight(height*scale);
        ui->gphPic1->setMaximumWidth(width*scale);
        ui->gphPic2->setMaximumWidth(width*scale);
        ui->gphPic3->setMaximumWidth(width*scale);
        ui->gphPic4->setMaximumWidth(width*scale);

        ui->gphPic1->mResizeRatio = scale;
        ui->gphPic2->mResizeRatio = scale;
        ui->gphPic3->mResizeRatio = scale;
        ui->gphPic4->mResizeRatio = scale;




        /*
        for(int i = 0; i < 4; i++)
            scene[i]->setSceneRect(0,0,ui->gphPic1->width(),ui->gphPic1->height());
            */
    }
}

/*****************************************************************************
 * Retreive next frame, find the target and display
 *****************************************************************************/
void MainWindow::getNextFrame()
{
    mCurrentFrames = vids.nextframe();

    for (int i = 0; i < 4; i++)
    {
        cv::Mat img;
        mCurrentFrames[i].copyTo(img);
        bool out = mpMST[i]->findTarget(img, mCandidateRect[i]);
        qDebug() << "next frame of " << i << " is " << out;
        picture[i]->setPixmap(fromMat(mCurrentFrames[i]));
    }
    ui->gphPic1->setTrackingRect(mCandidateRect[0]);
    ui->gphPic2->setTrackingRect(mCandidateRect[1]);
    ui->gphPic3->setTrackingRect(mCandidateRect[2]);
    ui->gphPic4->setTrackingRect(mCandidateRect[3]);

    for(int i=0;i<4;i++)
    {
        int x_pos = 0;
        int y_pos = 0;
        x_pos = mCandidateRect[i].x + mCandidateRect[i].width/2;
        y_pos = mCandidateRect[i].y + mCandidateRect[i].height/2;

        qDebug() << " Writing " << x_pos << " " << y_pos << " To " << i;

        (*mpTextStream[i]) << x_pos << " " << y_pos << "\n";
        mpTextStream[i]->flush();
    }
}

/*****************************************************************************
 *
 *****************************************************************************/
void MainWindow::paintEvent(QPaintEvent* e)
{
    if (mMainWindowStatus == IMAGE_NOT_LOADED)
    {
        ui->btnCmdSelect->setText(STR_SELECT_OBJ);
        ui->btnCmdSelect->setEnabled(false);
        ui->btnNextFrame->setEnabled(false);
        ui->cmdPlay->setEnabled(false);
    }
    else if(mMainWindowStatus==NORMAL)
    {
        ui->btnCmdSelect->setText(STR_SELECT_OBJ);
        ui->btnCmdSelect->setEnabled(true);
        ui->btnNextFrame->setEnabled(true);
        ui->cmdPlay->setEnabled(true);
    }
    else if(mMainWindowStatus==RECT_DRAWING)
    {
        ui->btnCmdSelect->setText(STR_FINISH_SELECT);
        ui->btnCmdSelect->setEnabled(true);
        ui->btnNextFrame->setEnabled(false);
        ui->cmdPlay->setEnabled(false);
    }
    else if(mMainWindowStatus==TRACKING)
    {
        ui->btnCmdSelect->setText(STR_SELECT_OBJ);
        ui->btnCmdSelect->setEnabled(true);
        ui->btnNextFrame->setEnabled(true);
        ui->cmdPlay->setEnabled(true);
    }

    QMainWindow::paintEvent(e);
}

/*****************************************************************************
 * Load a file (JSON format that describes each video as well as the starting
 * frame to sync the videos up).
 *****************************************************************************/
void MainWindow::on_cmdLoad_clicked()
{
    QFileDialog diagfile;
    QString file = diagfile.getOpenFileName();
    if (file == "")
        return;

    vids.readFile(file);

    qDebug() << "Reading first frame";
    mReferenceFrames = vids.firstframe();

    qDebug() << "Frames size: " << mReferenceFrames.size();
    qDebug() << "Frames type: " << mReferenceFrames[0].type();

    for (int i = 0; i < 4; i++)
    {
        picture[i]->setPixmap(fromMat(mReferenceFrames[i]));
    }
    mMainWindowStatus = NORMAL;
    resize();

}

/*****************************************************************************
 * Playing the video
 *****************************************************************************/
void MainWindow::on_cmdPlay_clicked()
{
    if (!timerrunning)
    {
        timer->start(TIMER_LENGTH);
        timerrunning = true;
        ui->cmdPlay->setText("Stop");
    }
    else
    {
        timer->stop();
        timerrunning = false;
        ui->cmdPlay->setText("Play");
    }
}

/*****************************************************************************
 * Load a single next frame
 *****************************************************************************/
void MainWindow::on_btnNextFrame_clicked()
{
    getNextFrame();
}

/*****************************************************************************
 * Allows the user to select a square
 *****************************************************************************/
void MainWindow::on_btnCmdSelect_clicked()
{
    if(mMainWindowStatus==NORMAL)
    {
        ui->gphPic1->enableRectDrawing(true);
        ui->gphPic2->enableRectDrawing(true);
        ui->gphPic3->enableRectDrawing(true);
        ui->gphPic4->enableRectDrawing(true);
        mMainWindowStatus = RECT_DRAWING;
    }
    else if(mMainWindowStatus==RECT_DRAWING)
    {
        ui->gphPic1->enableRectDrawing(false);
        ui->gphPic2->enableRectDrawing(false);
        ui->gphPic3->enableRectDrawing(false);
        ui->gphPic4->enableRectDrawing(false);
        mMainWindowStatus = NORMAL;

        mReferenceRect[0] = ui->gphPic1->getTrackingRect();
        mReferenceRect[1] = ui->gphPic2->getTrackingRect();
        mReferenceRect[2] = ui->gphPic3->getTrackingRect();
        mReferenceRect[3] = ui->gphPic4->getTrackingRect();
        for(int i=0;i<4;i++)
        {
            cv::Mat referenceModal = mpMST[i]->buildModel(mReferenceFrames[i], mReferenceRect[i]);
            mpMST[i]->setTargetModel(referenceModal);
            mCandidateRect[i] = mReferenceRect[i];
        }
    }
}

/*****************************************************************************
 * Timer has fired, load the next frame
 *****************************************************************************/
void MainWindow::timerupdate()
{
    getNextFrame();
}

