#include "icamera.h"

/*****************************************************************************
 *
 *****************************************************************************/
ICamera::ICamera() : Input()
{
    vidOpen = false;
}

/*****************************************************************************
 *
 *****************************************************************************/
int ICamera::getNumFrames()
{
    return -1;
}

/*****************************************************************************
 *
 *****************************************************************************/
QVector<Data*> ICamera::getNextFrame()
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
 *
 *****************************************************************************/
QString ICamera::getName()
{
    return QString("Camera");
}

/*****************************************************************************
 *
 *****************************************************************************/
QString ICamera::getCaption()
{
    return QString("Camera");
}

/*****************************************************************************
 *
 *****************************************************************************/
QVector<DatInfo> ICamera::getOutputTypes()
{
    QVector<DatInfo> ans;

    ans.push_back(DatInfo(IMAGE3, "Frame"));

    return ans;
}

/*****************************************************************************
 *
 *****************************************************************************/
QVector<Data*> ICamera::getCurrentFrame()
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
 *
 *****************************************************************************/
void ICamera::setFrameNum(int)
{
    return;
}

/*****************************************************************************
 *
 *****************************************************************************/
void ICamera::showConfig()
{
    config.exec();

    if (config.OkClicked())
    {
        reloadVideo();
    }
}

/*****************************************************************************
 *
 *****************************************************************************/
void ICamera::setData(QMap<QString, QVariant> data)
{
    if (data.contains("CameraId"))
    {
        config.setCameraId(data["CameraId"].toInt());
    }
}

/*****************************************************************************
 *
 *****************************************************************************/
void ICamera::reset()
{

}

/*****************************************************************************
 *
 *****************************************************************************/
QMap<QString, QVariant> ICamera::getData()
{
    QMap<QString, QVariant> ans;

    ans.insert("Name", QVariant(getName()));
    ans.insert("CameraId", QVariant(config.getCameraId()));

    return ans;
}

/*****************************************************************************
 *
 *****************************************************************************/
void ICamera::reloadVideo()
{
    if (vid.open(config.getCameraId()))
    {
        currLocation = 0;
        vidOpen = true;
    }
    else
    {
        vidOpen = false;
    }
}

static InputFactory<ICamera> iCamera;
