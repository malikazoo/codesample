#include "interactivevideocontroller.h"
#include <QSlider>
#include <QStyle>
#include <QToolButton>
#include <QHBoxLayout>

InteractiveVideoController::InteractiveVideoController(QWidget *parent)
    : QWidget(parent)
{
    mpPlayButton = new QToolButton(this);
    mpPlayButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    connect(mpPlayButton, SIGNAL(clicked()), this, SLOT(playClicked()));

    mpStopButton = new QToolButton(this);
    mpStopButton->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
    mpStopButton->setEnabled(false);
    connect(mpStopButton, SIGNAL(clicked()), this, SIGNAL(stop()));

    mpSlider = new QSlider(Qt::Horizontal, this);
    mpSlider->setRange(0, 100);

    mpLayout = new QHBoxLayout(this);
    mpLayout->addWidget(mpPlayButton);
    mpLayout->addWidget(mpStopButton);
    mpLayout->addWidget(mpSlider);

    this->setLayout(mpLayout);

}

void InteractiveVideoController::setState(QMediaPlayer::State state)
{
    if (state != mPlayerState)
    {
        mPlayerState = state;

        switch (state) {
        case QMediaPlayer::StoppedState:
            mpStopButton->setEnabled(false);
            mpPlayButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
            break;
        case QMediaPlayer::PlayingState:
            mpStopButton->setEnabled(true);
            mpPlayButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
            break;
        case QMediaPlayer::PausedState:
            mpStopButton->setEnabled(true);
            mpPlayButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
            break;
        }
    }
}

void InteractiveVideoController::playClicked()
{
    switch (mPlayerState) {
    case QMediaPlayer::StoppedState:
    case QMediaPlayer::PausedState:
        emit play();
        break;
    case QMediaPlayer::PlayingState:
        emit pause();
        break;
    }
}

void InteractiveVideoController::setSliderDuration(qint64 duration)
{
    if(mpSlider)
    {
        mpSlider->setMaximum(duration);
    }
}

void InteractiveVideoController::setSliderPosition(qint64 position)
{
    if(mpSlider)
    {
        mpSlider->setValue(position);
    }
}
