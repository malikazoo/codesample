#ifndef PICVIEWER_H
#define PICVIEWER_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QDebug>
#include <QGraphicsRectItem>

#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

class picviewer : public QGraphicsView
{
        Q_OBJECT
    public:
        explicit picviewer(QWidget *parent = 0);

        void enableRectDrawing(bool enable);
        bool isRectDrawingEnabled() { return mEnableRectDrawing; }
        QRect getDrawingRect() { return mDrawingRect; }

        cv::Rect getTrackingRect();
        void setTrackingRect(cv::Rect rect);
        void setDrawingRect(cv::Rect rect);

        double mResizeRatio;
        int    mDisplayXOffset;
        int    mDisplayYOffset;

    signals:

    protected:
        virtual void mousePressEvent(QMouseEvent *event);
        virtual void mouseReleaseEvent(QMouseEvent *event);
        virtual void mouseMoveEvent(QMouseEvent *event);

        virtual void paintEvent(QPaintEvent* e);

    public slots:

    private:
        QRect mDrawingRect;

        bool mEnableRectDrawing;
        bool mDrawing;

        int mStartX;
        int mStartY;
        int mEndX;
        int mEndY;

};

#endif // PICVIEWER_H
