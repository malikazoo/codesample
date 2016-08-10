#include "videosurface.h"

VideoSurface::VideoSurface(QObject *parent) :
    QAbstractVideoSurface(parent)
{
}

bool VideoSurface::present(const QVideoFrame &frame)
{
    qDebug() << "Found" << endl;
    return true;
}

QList<QVideoFrame::PixelFormat> VideoSurface::supportedPixelFormats(QAbstractVideoBuffer::HandleType handleType) const
{
    QList<QVideoFrame::PixelFormat> ans;
    ans.append(QVideoFrame::Format_ARGB32);
    ans.append(QVideoFrame::Format_ARGB32_Premultiplied);
    ans.append(QVideoFrame::Format_RGB32);
    ans.append(QVideoFrame::Format_RGB565);
    ans.append(QVideoFrame::Format_RGB555);

    return ans;
}

bool VideoSurface::isFormatSupported(const QVideoSurfaceFormat &format) const
{
    qDebug() << "Testing format: " << format.pixelFormat() << " " <<  format.frameWidth() << "x" << format.frameHeight() << endl;
    return true;
}
