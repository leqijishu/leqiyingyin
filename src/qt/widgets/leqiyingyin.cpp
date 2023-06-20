#include "leqiyingyin.h"
#include "constants.h"
#include "leqititlebar.h"
#include "leqivideowidget.h"
#include "leqicontrolbar.h"

#include <QVBoxLayout>
#include <QMediaPlayer>
#include <QFileDialog>
#include <QAudioOutput>
#include <QKeyEvent>
#include <QApplication>
#include <QFile>
#include <QStyle>
#include <QAudio>
#include <QSlider>
#include <QMediaMetaData>
#include <QSettings>
#include <QStandardPaths>

LeqiYingYin::LeqiYingYin(QWidget *parent)
    : QWidget(parent)
    , mainWindowSize(800, 600)
{
    initMainWindow();
    readSettings();
}

LeqiYingYin::~LeqiYingYin()
{    
}

void LeqiYingYin::initMainWindow()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(createTitleBar());
    mainLayout->addWidget(createVideoWidget());
    mainLayout->addWidget(createControlBar());
    mainLayout->setContentsMargins(0, 0, 0, 0);
    resize(mainWindowSize);
    setWindowFlag(Qt::FramelessWindowHint);
    loadStyleSheet("dark");
    setWindowIcon(QIcon(":/resources/logo/leqi.ico"));

    connect(leqiVideoWidget, SIGNAL(fullScreenChanged(bool)), leqiTitleBar, SLOT(setFullScreen(bool)));
    connect(leqiVideoWidget, SIGNAL(fullScreenChanged(bool)), leqiControlBar, SLOT(setFullScreen(bool)));
}

LeqiTitleBar* LeqiYingYin::createTitleBar()
{
    leqiTitleBar = new LeqiTitleBar;

    connect(leqiTitleBar, &LeqiTitleBar::titleBarOpen, this, &LeqiYingYin::openFile);
    connect(leqiTitleBar, SIGNAL(titleBarPlay()), this, SLOT(openFile()));
    connect(leqiTitleBar, SIGNAL(titleBarPause()), this, SLOT(togglePauseOrPlay()));
    connect(leqiTitleBar, SIGNAL(titleBarStop()), this, SLOT(stopPlaying()));
    connect(leqiTitleBar, SIGNAL(titleBarMute()), this, SLOT(toggleMute()));
    connect(leqiTitleBar, SIGNAL(titleBarAudioTrack(int)), this, SLOT(setAudioTrack(int)));
    connect(leqiTitleBar, SIGNAL(fullScreen()), this, SLOT(toggleFullScreen()));
    connect(leqiTitleBar, SIGNAL(minimizeWindow()), this, SLOT(showMinimized()));
    connect(leqiTitleBar, SIGNAL(closeWindow()), this, SLOT(close()));
    connect(this, SIGNAL(setTitle(QString)), leqiTitleBar, SLOT(setTitle(QString)));
    connect(this, SIGNAL(setAudioTracks(QList<QMediaMetaData>))
            , leqiTitleBar, SLOT(setAudioTracksMenu(QList<QMediaMetaData>)));

    return leqiTitleBar;
}

LeqiVideoWidget* LeqiYingYin::createVideoWidget()
{
    leqiVideoWidget = new LeqiVideoWidget(this);
    player = new QMediaPlayer;
    player->setVideoOutput(leqiVideoWidget);
    audioOutput = new QAudioOutput;
    player->setAudioOutput(audioOutput);
    audioOutput->setVolume(0.4);
    QHBoxLayout *videoLayout = new QHBoxLayout;
    videoLayout->addWidget(leqiVideoWidget);

    connect(leqiVideoWidget, SIGNAL(videoOpen()), this, SLOT(openFile()));
    connect(leqiVideoWidget, SIGNAL(videoPlay()), this, SLOT(openFile()));
    connect(leqiVideoWidget, SIGNAL(videoPause()), this, SLOT(togglePauseOrPlay()));
    connect(leqiVideoWidget, SIGNAL(videoStop()), this, SLOT(stopPlaying()));
    connect(leqiVideoWidget, SIGNAL(videoMute()), this, SLOT(toggleMute()));
    connect(leqiVideoWidget, SIGNAL(videoAudioTrack(int)), this, SLOT(setAudioTrack(int)));
    connect(leqiVideoWidget, &LeqiVideoWidget::togglePauseOrPlay, this, &LeqiYingYin::togglePauseOrPlay);
    connect(leqiVideoWidget, SIGNAL(openFile()), this, SLOT(openFile()));
    connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    connect(player, SIGNAL(durationChanged(qint64)), this, SLOT(durationChanged(qint64)));
    connect(player, SIGNAL(tracksChanged()), this, SLOT(tracksChanged()));
    connect(this, SIGNAL(setAudioTracks(QList<QMediaMetaData>))
            , leqiVideoWidget, SLOT(setAudioTracksMenu(QList<QMediaMetaData>)));
    connect(leqiVideoWidget, SIGNAL(videoForwardFive()), this, SLOT(forwardFive()));
    connect(leqiVideoWidget, SIGNAL(videoBackwardFive()), this, SLOT(backwardFive()));

    return leqiVideoWidget;
}

LeqiControlBar* LeqiYingYin::createControlBar()
{
    leqiControlBar = new LeqiControlBar(this);

    connect(leqiControlBar, SIGNAL(barOpen()), this, SLOT(openFile()));
    connect(leqiControlBar, SIGNAL(barPlay()), this, SLOT(openFile()));
    connect(leqiControlBar, SIGNAL(barPause()), this, SLOT(togglePauseOrPlay()));
    connect(leqiControlBar, SIGNAL(barStop()), this, SLOT(stopPlaying()));
    connect(leqiControlBar, SIGNAL(barMute()), this, SLOT(toggleMute()));
    connect(leqiControlBar, SIGNAL(barVolume(int)), this, SLOT(setVolume(int)));
    connect(leqiControlBar, SIGNAL(barPosition(int)), this, SLOT(setPosition(int)));
    connect(this, SIGNAL(setRange(int,int)), leqiControlBar, SLOT(setPositionRange(int,int)));
    connect(this, SIGNAL(setDuration(QString)), leqiControlBar, SLOT(setDuration(QString)));
    connect(this, SIGNAL(setVoiceIcon(QString,QString)),
            leqiControlBar, SLOT(setVoiceIcon(QString,QString)));
    connect(leqiControlBar, SIGNAL(barForwardFive()), this, SLOT(forwardFive()));
    connect(leqiControlBar, SIGNAL(barBackwardFive()), this, SLOT(backwardFive()));
    connect(leqiControlBar, SIGNAL(barUp()), this, SLOT(volumeUp()));
    connect(leqiControlBar, SIGNAL(barDown()), this, SLOT(volumeDown()));

    return leqiControlBar;
}

void LeqiYingYin::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(
        this,
        TIP_OPEN,
        defaultDir,
        "*.*");
    if (fileName.isEmpty())
    {
        return;
    }
    
    player->setSource(fileName);
    leqiVideoWidget->setSource(fileName);
    player->play();
    emit setTitle(QFileInfo(fileName).baseName());
    emit setRange(0, player->duration());
    setWindowTitle(QFileInfo(fileName).baseName());
    defaultDir = QFileInfo(fileName).path();
    saveSettings();

    disconnect(leqiTitleBar, SIGNAL(titleBarPlay()), this, SLOT(openFile()));
    connect(leqiTitleBar, SIGNAL(titleBarPlay()), player, SLOT(play()));
    disconnect(leqiVideoWidget, SIGNAL(videoPlay()), this, SLOT(openFile()));
    connect(leqiVideoWidget, SIGNAL(videoPlay()), player, SLOT(play()));
    disconnect(leqiControlBar, SIGNAL(barPlay()), this, SLOT(openFile()));
    connect(leqiControlBar, SIGNAL(barPlay()), player, SLOT(play()));
}

void LeqiYingYin::stopPlaying()
{
    player->stop();
    player->setSource(QUrl(""));
    leqiVideoWidget->setSource("");
    emit setTitle("");

    connect(leqiTitleBar, SIGNAL(titleBarPlay()), this, SLOT(openFile()));
    connect(leqiVideoWidget, SIGNAL(videoPlay()), this, SLOT(openFile()));
    connect(leqiControlBar, SIGNAL(barPlay()), this, SLOT(openFile()));
}

void LeqiYingYin::setPosition(int position)
{
    player->setPosition(position);
}

void LeqiYingYin::positionChanged(qint64 position)
{
    leqiControlBar->setValue(position);
    updateDurationInfo(position / 1000);
}

void LeqiYingYin::durationChanged(qint64 duration)
{
    nDuration = duration / 1000;
    leqiControlBar->setRange(0, duration);
}

void LeqiYingYin::toggleFullScreen()
{
    leqiVideoWidget->setFullScreen(!isFullScreen());
}

void LeqiYingYin::pauseOrPlay()
{
    switch (player->playbackState())
    {
    case QMediaPlayer::PlayingState:
        player->pause();
        break;
    case QMediaPlayer::PausedState:
        player->play();
        break;
    default:
        break;
    }
}

void LeqiYingYin::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Return:
    case Qt::Key_Enter:
        leqiVideoWidget->setFullScreen(!leqiVideoWidget->isFullScreen());
        event->accept();
        break;
    case Qt::Key_Space:
        togglePauseOrPlay();
        event->accept();
        break;
    case Qt::Key_Up:
        volumeUp();
        event->accept();
        break;
    default:
        QWidget::keyPressEvent(event);
        break;
    }
}

void LeqiYingYin::togglePauseOrPlay()
{
    if (player->source().isEmpty())
    {
        openFile();
        return;
    }
    
    pauseOrPlay();
}

void LeqiYingYin::toggleMute()
{
    if (player->source().isEmpty())
    {
        return;
    }
    
    audioOutput->setMuted(!audioOutput->isMuted());
    if (audioOutput->isMuted())
    {
        emit setVoiceIcon(":/resources/images/mute-8a.svg", TIP_CANCEL_MUTE);
        return;
    }

    emit setVoiceIcon(":/resources/images/voice-8a.svg", TIP_MUTE);
}

void LeqiYingYin::updateDurationInfo(qint64 currentInfo)
{
    QString durationInfo;
    if (currentInfo || nDuration)
    {
        QTime currentTime((currentInfo / 3600) % 60, (currentInfo / 60) % 60,
            currentInfo % 60, (currentInfo * 1000) % 1000);
        QTime totalTime((nDuration / 3600) % 60, (nDuration / 60) % 60,
            nDuration % 60, (nDuration * 1000) % 1000);
        QString format = "mm:ss";
        if (nDuration > 3600)
        {
            format = "hh:mm:ss";
        }
        
        durationInfo = currentTime.toString(format) + " / " + totalTime.toString(format);
    }
    
    emit setDuration(durationInfo);
}

void LeqiYingYin::loadStyleSheet(const QString &sheetName)
{
    QFile file(":/resources/qss/" + sheetName.toLower() + ".qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QString::fromLatin1(file.readAll());
    qApp->setStyleSheet(styleSheet);
}

void LeqiYingYin::readSettings()
{
    QString iniSettings = QDir::currentPath() + settingsName;
    if (!QFile::exists(iniSettings))
    {
        setDefaultDir();
        saveSettings("basic", "MoviesLocation", defaultDir);
        return;
    }

    QSettings settings(iniSettings, QSettings::IniFormat);
    settings.beginGroup("basic");
    QString moviesLocation = settings.value("MoviesLocation").toString();
    settings.endGroup();
    if (moviesLocation.isEmpty() || !QDir(moviesLocation).exists())
        setDefaultDir();
    else
        defaultDir = moviesLocation;
}

void LeqiYingYin::saveSettings()
{
    if (defaultDir.isEmpty())
    {
        setDefaultDir();
    }

    saveSettings("basic", "MoviesLocation", defaultDir);
}

void LeqiYingYin::saveSettings(const QString &group, const QString &key, const QString &value)
{
    QString iniSettings = QDir::currentPath() + settingsName;
    QSettings settings(iniSettings, QSettings::IniFormat);
    settings.beginGroup(group);
    settings.setValue(key, value);
    settings.endGroup();
}

void LeqiYingYin::setDefaultDir()
{
    defaultDir = QStandardPaths::standardLocations(
            QStandardPaths::MoviesLocation
            )
            .value(0, QDir::homePath())
        ;
}

void LeqiYingYin::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        clickPosition = event->position().toPoint();
    }
}

void LeqiYingYin::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton
        && event->pos().x() >= 0
        && event->pos().y() >= 0
        && event->pos().x() <= geometry().width()
        && event->pos().y() <= (geometry().height() - leqiControlBar->height())
        )
    {
        move(event->position().toPoint() + pos() - clickPosition);
    }
}

void LeqiYingYin::setVolume(int value)
{
    qreal volume = value / qreal(100.0);
    audioOutput->setVolume(volume);
}

void LeqiYingYin::tracksChanged()
{
    emit setAudioTracks(player->audioTracks());
}

void LeqiYingYin::setAudioTrack(int index)
{
    player->setActiveAudioTrack(index);
}

void LeqiYingYin::forwardFive()
{
    qint64 position = player->position() + 5 * 1000;
    setPosition(position);
}

void LeqiYingYin::backwardFive()
{
    qint64 position = player->position() - 5 * 1000;
    setPosition(position);
}

void LeqiYingYin::volumeUp()
{
    qreal volume = audioOutput->volume() + 5 / qreal(100.0);
    audioOutput->setVolume(volume);
}

void LeqiYingYin::volumeDown()
{
    qreal volume = audioOutput->volume() - 5 / qreal(100.0);
    audioOutput->setVolume(volume);
}
