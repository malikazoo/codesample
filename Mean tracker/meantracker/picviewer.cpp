#include "picviewer.h"

/*****************************************************************************
 *
 *****************************************************************************/
picviewer::picviewer(QWidget *parent) :
    QGraphicsView(parent)
{
    mDrawing = false;
    mEnableRectDrawing = false;

    mStartX = 0;
    mStartY = 0;
    mEndX = 0;
    mEndY = 0;

    mDrawingRect.setX(0);
    mDrawingRect.setY(0);
    mDrawingRect.setWidth(0);
    mDrawingRect.setHeight(0);

    mResizeRatio = 1.0;
    mDisplayXOffset = 0;
    mDisplayYOffset = 0;
}

/*****************************************************************************
 *
 *****************************************************************************/
void picviewer::enableRectDrawing(bool enable)
{
    mEnableRectDrawing = enable;
    mDrawing = false;
}

/*****************************************************************************
 * Mouse has been pressed to start drawing rectangle
 *****************************************************************************/
void picviewer::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);

    if(mEnableRectDrawing)
    {
        mStartX = event->x();
        mStartY = event->y();

        mDrawingRect.setX(0);
        mDrawingRect.setY(0);
        mDrawingRect.setWidth(0);
        mDrawingRect.setHeight(0);

        mDrawing = true;
        this->viewport()->update();
    }
}

/*****************************************************************************
 * Mouse has been released to finish drawing rectangle
 *****************************************************************************/
void picviewer::mouseReleaseEvent(QMouseEvent *event)
{
    QGraphicsView::mouseReleaseEvent(event);
    if(mEnableRectDrawing)
    {
        mDrawing = false;
        this->viewport()->update();
    }
}

/*****************************************************************************
 * User is currently drawing rectangle, update to show rectangle as is
 *****************************************************************************/
void picviewer::mouseMoveEvent(QMouseEvent *event)
{
    QGraphicsView::mouseMoveEvent(event);
    if(mEnableRectDrawing)
    {
        if(mDrawing)
        {
            mEndX = event->x();
            mEndY = event->y();

            int ul_x = mStartX<mEndX?mStartX:mEndX;
            int ul_y = mStartY<mEndY?mStartY:mEndY;
            int width = abs(mStartX - mEndX);
            int height = abs(mStartY - mEndY);

            mDrawingRect.setX(ul_x);
            mDrawingRect.setY(ul_y);
            mDrawingRect.setWidth(width);
            mDrawingRect.setHeight(height);

            //qDebug() << "Update " << mDrawingRect.x() << " " << mDrawingRect.y() << " " << mDrawingRect.width() << " " << mDrawingRect.height();
            this->viewport()->update();
        }
    }
}

/*****************************************************************************
 *
 *****************************************************************************/
void picviewer::paintEvent(QPaintEvent* e)
{
    QGraphicsView::paintEvent(e);

    //qDebug() << "Paint called";
    if(mDrawingRect.width() >0 || mDrawingRect.height() > 0)
    {
        QPainter painter(this->viewport());
        QPen green_pen(QColor(0,255,0));
        painter.setPen(green_pen);

        painter.drawRect(mDrawingRect.x(), mDrawingRect.y(), mDrawingRect.width(), mDrawingRect.height());
    }

}

/*****************************************************************************
 *
 *****************************************************************************/
cv::Rect picviewer::getTrackingRect()
{
    int new_x = (mDrawingRect.x() - mDisplayXOffset)/mResizeRatio;
    int new_y = (mDrawingRect.y() - mDisplayYOffset)/mResizeRatio;
    int new_width = mDrawingRect.width() / mResizeRatio;
    int new_height = mDrawingRect.height() / mResizeRatio;
    //cv::Rect trackingRect(mDrawingRect.x(), mDrawingRect.y(), mDrawingRect.width(), mDrawingRect.height());
    cv::Rect trackingRect(new_x, new_y, new_width, new_height);
    return trackingRect;
}

/*****************************************************************************
 *
 *****************************************************************************/
void picviewer::setTrackingRect(cv::Rect rect)
{
    int new_x = (rect.x + mDisplayXOffset) * mResizeRatio;
    int new_y = (rect.y+ mDisplayYOffset) * mResizeRatio;
    int new_width = rect.width * mResizeRatio;
    int new_height = rect.height * mResizeRatio;
    /*
    mDrawingRect.setX(rect.x);
    mDrawingRect.setY(rect.y);
    mDrawingRect.setWidth(rect.width);
    mDrawingRect.setHeight(rect.height);
    */
    mDrawingRect.setX(new_x);
    mDrawingRect.setY(new_y);
    mDrawingRect.setWidth(new_width);
    mDrawingRect.setHeight(new_height);
}


void picviewer::setDrawingRect(cv::Rect rect)
{
    mDrawingRect.setX(rect.x);
    mDrawingRect.setY(rect.y);
    mDrawingRect.setWidth(rect.width);
    mDrawingRect.setHeight(rect.height);
}
