#ifndef INTERACTIVEVIDEOPLAYER_H
#define INTERACTIVEVIDEOPLAYER_H

#include <QGraphicsView>

class InteractiveGraphicsView : public QGraphicsView
{
    Q_OBJECT

public:
    InteractiveGraphicsView(QWidget *parent = 0);
    ~InteractiveGraphicsView();

protected:
    void mouseReleaseEvent(QMouseEvent * e);
    void mousePressEvent(QMouseEvent * e);
    void mouseMoveEvent(QMouseEvent * e);

    void paintEvent(QPaintEvent* e);

private:
    int mRectStartX;
    int mRectStartY;
    int mRectEndX;
    int mRectEndY;
    bool mDrawingRect;
    QPoint * mpInitPoint;
    QPoint * mpEndPoint;
};

#endif // INTERACTIVEVIDEOPLAYER_H
