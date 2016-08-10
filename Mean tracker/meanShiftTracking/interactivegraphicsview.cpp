#include "interactivegraphicsview.h"
#include <QPainter>
#include <QMouseEvent>

InteractiveGraphicsView::InteractiveGraphicsView(QWidget *parent)
    : QGraphicsView(parent)
{
    setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

    QPalette p = palette();
    p.setColor(QPalette::Window, Qt::black);
    setPalette(p);

    setAttribute(Qt::WA_OpaquePaintEvent);

    mpInitPoint = new QPoint(0,0);
    mpEndPoint = new QPoint(0,0);
    mDrawingRect = false;
    mRectStartX = 0;
    mRectStartY = 0;
    mRectEndX = 0;
    mRectEndY = 0;
}

InteractiveGraphicsView::~InteractiveGraphicsView()
{
    if(mpInitPoint)
    {
        delete mpInitPoint;
        mpInitPoint = NULL;
    }
    if(mpEndPoint)
    {
        delete mpEndPoint;
        mpEndPoint= NULL;
    }
}


void InteractiveGraphicsView::paintEvent(QPaintEvent* e)
{
     QGraphicsView::paintEvent(e);

     if(mpInitPoint->x()!= mpEndPoint->x() || mpInitPoint->y()!=mpEndPoint->y())
     {
         QPainter painter(this->viewport());
         QPen green_pen(QColor(0,255,0));
         painter.setPen(green_pen);

         mRectStartX = mpInitPoint->x()<= mpEndPoint->x() ?  mpInitPoint->x(): mpEndPoint->x();
         mRectStartY = mpInitPoint->y()<= mpEndPoint->y() ?  mpInitPoint->y(): mpEndPoint->y();
         mRectEndX   = mpInitPoint->x()> mpEndPoint->x() ?  mpInitPoint->x(): mpEndPoint->x();
         mRectEndY   = mpInitPoint->y()> mpEndPoint->y() ?  mpInitPoint->y(): mpEndPoint->y();

         painter.drawRect(mRectStartX, mRectStartY, mRectEndX - mRectStartX, mRectEndY - mRectStartY);
     }

}

void InteractiveGraphicsView::mousePressEvent ( QMouseEvent * e )
{
    if (e->button()==Qt::LeftButton)
    {
        mpInitPoint->setX(e->x());
        mpInitPoint->setY(e->y());
        mpEndPoint->setX(e->x());
        mpEndPoint->setY(e->y());
        mDrawingRect = true;

        update();
    }
}

void InteractiveGraphicsView::mouseMoveEvent( QMouseEvent * e )
{
    //if(e->button()==Qt::LeftButton)
    if(mDrawingRect==true)
    {
        mpEndPoint->setX(e->x());
        mpEndPoint->setY(e->y());
        update();
    }
}

void InteractiveGraphicsView::mouseReleaseEvent ( QMouseEvent * e )
{
    if(e->button()==Qt::LeftButton)
    {
        mpEndPoint->setX(e->x());
        mpEndPoint->setY(e->y());

        mRectStartX = mpInitPoint->x()<= mpEndPoint->x() ?  mpInitPoint->x(): mpEndPoint->x();
        mRectStartY = mpInitPoint->y()<= mpEndPoint->y() ?  mpInitPoint->y(): mpEndPoint->y();
        mRectEndX   = mpInitPoint->x()> mpEndPoint->x() ?  mpInitPoint->x(): mpEndPoint->x();
        mRectEndY   = mpInitPoint->y()> mpEndPoint->y() ?  mpInitPoint->y(): mpEndPoint->y();

        mRectStartX = mRectStartX >= 0 ? mRectStartX : 0;
        mRectStartY = mRectStartY >= 0 ? mRectStartY : 0;
        mRectEndX   = mRectEndX < this->width() ?  mRectEndX : this->width()-1;
        mRectEndY   = mRectEndY < this->height() ?  mRectEndY : this->height()-1;
    }
    mDrawingRect = false;
    update();
}
