#include "ivideo.h"

/*****************************************************************************
 *
 *****************************************************************************/
IVideo::IVideo(QObject* parent) : Input(parent)
{
    vidOpen = false;
}

/*****************************************************************************
 *
 *****************************************************************************/
IVideo::~IVideo()
{

}

/*****************************************************************************
 * Returns the number of frames total in the video
 *****************************************************************************/
int IVideo::getNumFrames()
{
    if (vidOpen)
        return vid.get(CV_CAP_PROP_FRAME_COUNT);
    else
        return 0;
}

/*****************************************************************************
 * Returns the next frame packaged up as a data object
 *****************************************************************************/
QVector<Data*> IVideo::getNextFrame()
{
    Mat nextframe;
    if (vidOpen)
    {
        DImage3* d = new DImage3();
        vid.read(nextframe);
        d->setImage(nextframe);
        QVector<Data*> ans;
        ans.push_back(d);
        return ans;
    }

    return QVector<Data*>();
}

/*****************************************************************************
 * Returns the name of the input (video)
 *****************************************************************************/
QString IVideo::getName()
{
    return QString("Video");
}

/*****************************************************************************
 * returns the caption placed on top of the input (video)
 *****************************************************************************/
QString IVideo::getCaption()
{
    return QString("Video");
}

/*****************************************************************************
 *
 *****************************************************************************/
QVector<DatInfo> IVideo::getOutputTypes()
{
    QVector<DatInfo> ans;

    ans.push_back(DatInfo(IMAGE3, "Frame"));

    return ans;
}

/*****************************************************************************
 *
 *****************************************************************************/
QVector<Data*> IVideo::getCurrentFrame()
{
    Mat nextframe;
    if (vidOpen)
    {
        DImage3* d = new DImage3();
        vid.retrieve(nextframe);
        d->setImage(nextframe);
        QVector<Data*> ans;
        ans.push_back(d);
        return ans;
    }

    return QVector<Data*>();
}

/*****************************************************************************
 * Sets the frame number of the video
 *****************************************************************************/
void IVideo::setFrameNum(int framenum)
{
    if (vidOpen)
    {
        vid.set(CV_CAP_PROP_POS_FRAMES, (double)framenum);
    }
}

/*****************************************************************************
 * Show the configuration window for the video
 *****************************************************************************/
void IVideo::showConfig()
{
    config.exec();

    if (config.OkClicked())
    {
        file = config.getFileName();
        reloadVideo();
    }

}

/*****************************************************************************
 *
 *****************************************************************************/
void IVideo::reset()
{

}

/*****************************************************************************
 *
 *****************************************************************************/
QMap<QString, QVariant> IVideo::getData()
{
    QMap<QString, QVariant> ans;

    ans.insert("Name", QVariant(getName()));
    ans.insert("File", QVariant(config.getFileName()));

    return ans;
}

/*****************************************************************************
 *
 *****************************************************************************/
void IVideo::setData(QMap<QString, QVariant> data)
{
    if (data.contains("File"))
    {
        file = data["File"].toString();
        config.setFileName(file);
    }
}

/*****************************************************************************
 * Refreshes the video that was set.
 *****************************************************************************/
void IVideo::reloadVideo()
{
    if (vid.open(file.toStdString()))
    {
        currLocation = 0;
        vidOpen = true;
    }
    else
    {
        vidOpen = false;
    }
}

static InputFactory<IVideo> iVideo;


