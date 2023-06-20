#include "leqicontrolbar.h"
#include "leqicontrols.h"
#include "constants.h"
#include "leqislider.h"

#include <QVBoxLayout>
#include <QSlider>
#include <QLabel>

LeqiControlBar::LeqiControlBar(QWidget *parent)
    : QWidget(parent)
    , isFullScreen(false)
{
    initialControlBar();
}

LeqiControlBar::~LeqiControlBar()
{}

void LeqiControlBar::initialControlBar()
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addLayout(createDurationLayout());
    LeqiControls *leqiControls = new LeqiControls;
    layout->addWidget(leqiControls);
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    connect(leqiControls, SIGNAL(controlOpen()), this, SLOT(open()));
    connect(leqiControls, SIGNAL(controlPlay()), this, SLOT(play()));
    connect(leqiControls, SIGNAL(controlPause()), this, SLOT(pause()));
    connect(leqiControls, SIGNAL(controlStop()), this, SLOT(stop()));
    connect(leqiControls, SIGNAL(controlMute()), this, SLOT(mute()));
    connect(leqiControls, SIGNAL(controlVolume(int)), this, SLOT(volume(int)));
    connect(this, SIGNAL(changeVoiceIcon(QString,QString)),
            leqiControls, SLOT(changeVoiceIcon(QString,QString)));
    connect(leqiControls, SIGNAL(controlUp()), this, SLOT(up()));
    connect(leqiControls, SIGNAL(controlDown()), this, SLOT(down()));
}

QHBoxLayout* LeqiControlBar::createDurationLayout()
{
    QHBoxLayout *durationLayout = new QHBoxLayout;
    positionSlider = new LeqiSlider;
    labelDuration = new QLabel(LABEL_DURATION);
    labelDuration->setObjectName("labelDuration");
    durationLayout->addWidget(positionSlider);
    durationLayout->addWidget(labelDuration);

    connect(positionSlider, SIGNAL(sliderMoved(int)), this, SLOT(setPosition(int)));
    connect(positionSlider, SIGNAL(seekPosition(int)), this, SLOT(setPosition(int)));
    connect(positionSlider, SIGNAL(forwardFive()), this, SLOT(forwardFive()));
    connect(positionSlider, SIGNAL(backwardFive()), this, SLOT(backwardFive()));

    return durationLayout;
}

void LeqiControlBar::open()
{
    emit barOpen();
}

void LeqiControlBar::play()
{
    emit barPlay();
}

void LeqiControlBar::pause()
{
    emit barPause();
}

void LeqiControlBar::stop()
{
    emit barStop();
}

void LeqiControlBar::mute()
{
    emit barMute();
}

void LeqiControlBar::volume(int volume)
{
    emit barVolume(volume);
}

void LeqiControlBar::setPosition(int position)
{
    emit barPosition(position);
}

void LeqiControlBar::setPositionRange(int min, int max)
{
    positionSlider->setRange(min, max);
}

void LeqiControlBar::setDuration(const QString &duration)
{
    labelDuration->setText(duration);
}

void LeqiControlBar::setValue(int value)
{
    positionSlider->setValue(value);
}

void LeqiControlBar::setRange(int min, int max)
{
    positionSlider->setRange(min, max);
}

void LeqiControlBar::setVoiceIcon(const QString &icon, const QString &tips)
{
    emit changeVoiceIcon(icon, tips);
}

void LeqiControlBar::forwardFive()
{
    emit barForwardFive();
}

void LeqiControlBar::backwardFive()
{
    emit barBackwardFive();
}

void LeqiControlBar::up()
{
    emit barUp();
}

void LeqiControlBar::down()
{
    emit barDown();
}

void LeqiControlBar::setFullScreen(bool state)
{
    isFullScreen = state;
}
