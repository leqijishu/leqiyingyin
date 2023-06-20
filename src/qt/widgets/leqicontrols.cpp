#include "leqicontrols.h"
#include "leqibutton.h"
#include "leqislider.h"
#include "constants.h"

#include <QHBoxLayout>
#include <QEvent>
#include <QKeyEvent>
#include <QApplication>

LeqiControls::LeqiControls(QWidget *parent)
    : QWidget(parent)
{
    initialControls();
}

LeqiControls::~LeqiControls()
{}

bool LeqiControls::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == volumeSlider)
    {
        if (event->type() == QEvent::KeyPress)
        {
            QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
            switch (keyEvent->key()) {
            case Qt::Key_Up:
            {
                QApplication::activeWindow();
                volumeSlider->activateWindow();
                volumeSlider->setFocus();
                int value = volumeSlider->value() + 5;
                volumeSlider->setValue(value);
                emit controlUp();
                keyEvent->accept();
            }
                break;
            case Qt::Key_Down:
            {
                QApplication::activeWindow();
                volumeSlider->setFocus();
                int value = volumeSlider->value() - 5;
                volumeSlider->setValue(value);
                emit controlDown();
                keyEvent->accept();
            }
                break;
            default:
                break;
            }

            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return QWidget::eventFilter(obj, event);
    }
}

void LeqiControls::initialControls()
{
    QHBoxLayout *controlLayout = new QHBoxLayout(this);
    LeqiButton *openButton = new LeqiButton(TIP_OPEN, "openButton");
    LeqiButton *playButton = new LeqiButton(TIP_PLAY, "playButton");
    LeqiButton *pauseButton = new LeqiButton(TIP_PAUSE, "pauseButton");
    LeqiButton *stopButton = new LeqiButton(TIP_STOP, "stopButton");
    voiceButton = new LeqiButton(TIP_MUTE);
    voiceButton->setIcon(QIcon(":/resources/images/voice-8a.svg"));
    voiceButton->setStyleSheet(":hover { icon: url(:/resources/images/voice.svg); }");
    volumeSlider = new LeqiSlider(this);
    volumeSlider->setRange(0, 100);
    volumeSlider->setValue(40);
    controlLayout->addStretch(1);
    controlLayout->addWidget(openButton);    
    controlLayout->addWidget(playButton);
    controlLayout->addWidget(pauseButton);
    controlLayout->addWidget(stopButton);
    controlLayout->addWidget(voiceButton);
    controlLayout->addWidget(volumeSlider);
    controlLayout->addStretch(1);
    volumeSlider->installEventFilter(this);

    connect(openButton, SIGNAL(clicked()), this, SLOT(open()));
    connect(playButton, SIGNAL(clicked()), this, SLOT(play()));
    connect(pauseButton, SIGNAL(clicked()), this, SLOT(pause()));
    connect(stopButton, SIGNAL(clicked()), this, SLOT(stop()));
    connect(voiceButton, SIGNAL(clicked()), this, SLOT(mute()));
    connect(volumeSlider, SIGNAL(valueChanged(int)), this, SLOT(volume(int)));
}

void LeqiControls::open()
{
    emit controlOpen();
}

void LeqiControls::play()
{
    emit controlPlay();
}

void LeqiControls::pause()
{
    emit controlPause();
}

void LeqiControls::stop()
{
    emit controlStop();
}

void LeqiControls::mute()
{
    emit controlMute();
}

void LeqiControls::volume(int volume)
{
    emit controlVolume(volume);
}

void LeqiControls::changeVoiceIcon(const QString &icon, const QString &tips)
{
    voiceButton->setIcon(QIcon(icon));
    voiceButton->setToolTip(tips);
    if (icon == ":/resources/images/mute-8a.svg")
    {
        voiceButton->setStyleSheet(":hover { icon: url(:/resources/images/mute.svg); }");
        return;
    }

    voiceButton->setStyleSheet(":hover { icon: url(:/resources/images/voice.svg); }");
}
