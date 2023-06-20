#include "leqivideowidget.h"
#include "leqimenu.h"

#include <QMouseEvent>

LeqiVideoWidget::LeqiVideoWidget(QWidget *parent)
    : QVideoWidget(parent)
{
    initialMenu();
}

LeqiVideoWidget::~LeqiVideoWidget()
{}

void LeqiVideoWidget::initialMenu()
{
    setAspectRatioMode(Qt::KeepAspectRatio);
    leqiMenu = new LeqiMenu(this);

    connect(leqiMenu, SIGNAL(menuOpen()), this, SLOT(open()));
    connect(leqiMenu, SIGNAL(menuPlay()), this, SLOT(play()));
    connect(leqiMenu, SIGNAL(menuPause()), this, SLOT(pause()));
    connect(leqiMenu, SIGNAL(menuStop()), this, SLOT(stop()));
    connect(leqiMenu, SIGNAL(menuMute()), this, SLOT(mute()));
    connect(this, SIGNAL(createAudioTracksMenu(QList<QMediaMetaData>))
            , leqiMenu, SLOT(createAudioTracksMenu(QList<QMediaMetaData>)));
    connect(leqiMenu, SIGNAL(menuAudioTrack(int)), this, SLOT(setAudioTrack(int)));
}

void LeqiVideoWidget::setSource(const QString &source)
{
    this->source = source;
}

void LeqiVideoWidget::open()
{
    emit videoOpen();
}

void LeqiVideoWidget::play()
{
    emit videoPlay();
}

void LeqiVideoWidget::pause()
{
    emit videoPause();
}

void LeqiVideoWidget::stop()
{
    emit videoStop();
}

void LeqiVideoWidget::mute()
{
    emit videoMute();
}

void LeqiVideoWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (source.isEmpty())
    {
        emit openFile();
        return;
    }
    
    switch (event->button()) {
    case Qt::LeftButton:
        setFullScreen(!isFullScreen());
        event->accept();
        break;
    default:
        QVideoWidget::mouseDoubleClickEvent(event);
        break;
    }
}

void LeqiVideoWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Escape:
    case Qt::Key_Backspace:
    case Qt::Key_Return:
    case Qt::Key_Enter:
        if (isFullScreen()) {
            setFullScreen(false);
            event->accept();
        }
        break;
    case Qt::Key_Space:
        if (source.isEmpty())
        {
            emit openFile();
            break;
        }

        emit togglePauseOrPlay();
        event->accept();
        break;
    case Qt::Key_Right:
        emit videoForwardFive();
        event->accept();
        break;
    case Qt::Key_Left:
        emit videoBackwardFive();
        event->accept();
        break;
    default:
        QVideoWidget::keyPressEvent(event);
        break;
    }
}

void LeqiVideoWidget::mousePressEvent(QMouseEvent *event)
{
    switch (event->button()) {
    case Qt::RightButton:
        leqiMenu->exec(QCursor::pos());
        event->accept();
        break;
    default:
        QVideoWidget::mousePressEvent(event);
        break;
    }
}

void LeqiVideoWidget::setAudioTracksMenu(const QList<QMediaMetaData> &audioTracks)
{
    emit createAudioTracksMenu(audioTracks);
}

void LeqiVideoWidget::setAudioTrack(int index)
{
    emit videoAudioTrack(index);
}
