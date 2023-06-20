#include "leqititlebar.h"
#include "constants.h"
#include "leqibutton.h"
#include "leqimenu.h"

#include <QHBoxLayout>
#include <QMediaMetaData>

LeqiTitleBar::LeqiTitleBar(QWidget *parent)
    : QWidget(parent)
    , isFullScreen(false)
{
    initialTitleBar();
}

LeqiTitleBar::~LeqiTitleBar()
{}

void LeqiTitleBar::enterEvent(QEnterEvent *event)
{
    if (isFullScreen)
    {
        setWindowFlags(Qt::WindowStaysOnTopHint);
        show();
        return;
    }
}

void LeqiTitleBar::leaveEvent(QEvent *event)
{
    if (isFullScreen)
    {
        hide();
        return;
    }
}

void LeqiTitleBar::initialTitleBar()
{
    QHBoxLayout *titleBarLayout = new QHBoxLayout(this);
    LeqiButton *leqiButton = new LeqiButton(TIP_APPMENU, "leqiButton", APP_NAME);
    leqiMenu = new LeqiMenu();
    leqiButton->setMenu(leqiMenu);
    titleBarLayout->addWidget(leqiButton);
    titleBarLayout->addStretch(1);
    labelTitle = new QLabel;
    labelTitle->setObjectName("labelTitle");
    titleBarLayout->addWidget(labelTitle);
    titleBarLayout->addStretch(1);
    LeqiButton *fullScreenButton = new LeqiButton(TIP_FULLSCREEN, "fullScreenButton");
    LeqiButton *minimizeButtton = new LeqiButton(TIP_MINIMIZE, "minimizeButton");
    LeqiButton *closeButton = new LeqiButton(TIP_CLOSE, "closeButton");
    titleBarLayout->addWidget(fullScreenButton);
    titleBarLayout->addWidget(minimizeButtton);
    titleBarLayout->addWidget(closeButton);
    titleBarLayout->setContentsMargins(3, 3, 3, 0);
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    connect(leqiMenu, SIGNAL(menuOpen()), this, SLOT(open()));
    connect(leqiMenu, SIGNAL(menuPlay()), this, SLOT(play()));
    connect(leqiMenu, SIGNAL(menuPause()), this, SLOT(pause()));
    connect(leqiMenu, SIGNAL(menuStop()), this, SLOT(stop()));
    connect(leqiMenu, SIGNAL(menuMute()), this, SLOT(mute()));
    connect(this, SIGNAL(createAudioTracksMenu(QList<QMediaMetaData>))
            , leqiMenu, SLOT(createAudioTracksMenu(QList<QMediaMetaData>)));
    connect(leqiMenu, SIGNAL(menuAudioTrack(int)), this, SLOT(setAudioTrack(int)));
    connect(fullScreenButton, SIGNAL(clicked()), this, SLOT(toggleFullScreen()));
    connect(minimizeButtton, SIGNAL(clicked()), this, SLOT(showMinimized()));
    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));
}

void LeqiTitleBar::open()
{
    emit titleBarOpen();
}

void LeqiTitleBar::play()
{
    emit titleBarPlay();
}

void LeqiTitleBar::pause()
{
    emit titleBarPause();
}

void LeqiTitleBar::stop()
{
    emit titleBarStop();
}

void LeqiTitleBar::mute()
{
    emit titleBarMute();
}

void LeqiTitleBar::setFullScreen(bool state)
{
    isFullScreen = state;
    setWindowFlags(Qt::WindowStaysOnTopHint);
    show();
}

void LeqiTitleBar::toggleFullScreen()
{
    emit fullScreen();
}

void LeqiTitleBar::showMinimized()
{
    emit minimizeWindow();
}

void LeqiTitleBar::close()
{
    emit closeWindow();
}

void LeqiTitleBar::setTitle(const QString &title)
{
    labelTitle->setText(title);
}

void LeqiTitleBar::setAudioTracksMenu(const QList<QMediaMetaData>& audioTracks)
{
    emit createAudioTracksMenu(audioTracks);
}

void LeqiTitleBar::setAudioTrack(int index)
{
    emit titleBarAudioTrack(index);
}
