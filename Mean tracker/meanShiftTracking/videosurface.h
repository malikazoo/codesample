#ifndef VIDEOSURFACE_H
#define VIDEOSURFACE_H

#include <QAbstractVideoSurface>
#include <QVideoSurfaceFormat>
#include <QDebug>

class VideoSurface : public QAbstractVideoSurface
{
        Q_OBJECT
    public:
        explicit VideoSurface(QObject *parent = 0);

        virtual bool present(const QVideoFrame &frame);

        QList<QVideoFrame::PixelFormat> supportedPixelFormats(QAbstractVideoBuffer::HandleType handleType) const;

        bool isFormatSupported(const QVideoSurfaceFormat &format) const;

    signals:

    public slots:

};

#endif // VIDEOSURFACE_H
