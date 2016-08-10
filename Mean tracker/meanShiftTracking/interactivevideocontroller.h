#ifndef INTERACTIVEVIDEOCONTROLLER_H
#define INTERACTIVEVIDEOCONTROLLER_H

#include <QWidget>
#include <QMediaPlayer>

class QAbstractButton;
class QSlider;
class QHBoxLayout;

class InteractiveVideoController : public QWidget
{
    Q_OBJECT

public:
    InteractiveVideoController(QWidget *parent = 0);

    void setSliderDuration(qint64 duration);
    void setSliderPosition(qint64 position);

public slots:
    void setState(QMediaPlayer::State state);

signals:
    void play();
    void pause();
    void stop();

private slots:
    void playClicked();

private:
    QMediaPlayer::State mPlayerState;
    QAbstractButton * mpPlayButton;
    QAbstractButton * mpStopButton;
    QSlider * mpSlider;
    QHBoxLayout * mpLayout;

};

#endif // INTERACTIVEVIDEOCONTROLLER_H
