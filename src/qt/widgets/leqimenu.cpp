#include "leqimenu.h"
#include "constants.h"

#include <QDesktopServices>
#include <QMessageBox>
#include <QUrl>
#include <QApplication>
#include <QActionGroup>

LeqiMenu::LeqiMenu(QWidget *parent)
    : QMenu(parent)
{
    initialMenu();
}

LeqiMenu::~LeqiMenu()
{}

void LeqiMenu::initialMenu()
{
    QAction *openAction = new QAction(ACTION_OPEN);
    openAction->setShortcut(QKeySequence::Open);
    addAction(openAction);
    addSeparator();
    QMenu *controlMenu = new QMenu(TIP_PLAY);
    QAction *playAction = new QAction(TIP_PLAY);
    QAction *pauseAction = new QAction(TIP_PAUSE);
    QAction *stopAction = new QAction(TIP_STOP);
    QAction *muteAction = new QAction(TIP_MUTE);
    controlMenu->addAction(playAction);
    controlMenu->addAction(pauseAction);
    controlMenu->addAction(stopAction);
    controlMenu->addAction(muteAction);
    addMenu(controlMenu);
    addSeparator();
    audioTracksMenu = new QMenu(ACTION_AUDIO_TRACKS);
    addMenu(audioTracksMenu);
    addSeparator();
    QMenu *helpMenu = new QMenu(ACTION_HELP);
    QAction *homeAction = new QAction(ACTION_HOME);
    QAction *aboutAction = new QAction(ACTION_ABOUT);
    helpMenu->addAction(homeAction);
    helpMenu->addSeparator();
    helpMenu->addAction(aboutAction);
    addMenu(helpMenu);
    addSeparator();
    QAction *quitAction = new QAction(ACTION_QUIT);
    quitAction->setShortcut(QKeySequence(Qt::ALT | Qt::Key_F4));
    addAction(quitAction);

    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));
    connect(playAction, SIGNAL(triggered()), this, SLOT(play()));
    connect(pauseAction, SIGNAL(triggered()), this, SLOT(pause()));
    connect(stopAction, SIGNAL(triggered()), this, SLOT(stop()));
    connect(muteAction, SIGNAL(triggered()), this, SLOT(mute()));
    connect(homeAction, SIGNAL(triggered()), this, SLOT(openHomePage()));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(showAboutDialog()));
    connect(quitAction, SIGNAL(triggered()), this, SLOT(quit()));
}

void LeqiMenu::createAudioTracksMenu(const QList<QMediaMetaData> &audioTracks)
{
    audioTracksMenu->clear();
    QActionGroup *actionGroup = new QActionGroup(this);    
    actionGroup->setExclusive(true);
    actions.clear();
    for(int i = 0; i < audioTracks.size(); ++i)
    {
        QString name = trackName(audioTracks.at(i), i);
        QAction *trackAction = new QAction(name);
        trackAction->setCheckable(true);
        audioTracksMenu->addAction(trackAction);
        actionGroup->addAction(trackAction);
        actions.append(trackAction);
    }

    connect(audioTracksMenu, SIGNAL(triggered(QAction*)), this, SLOT(setAudioTrack(QAction*)));
}

QString LeqiMenu::trackName(const QMediaMetaData &metaData, int index)
{
    QString name;
    QString title = metaData.stringValue(QMediaMetaData::Title);
    QLocale::Language lang = metaData.value(QMediaMetaData::Language).value<QLocale::Language>();
    if (title.isEmpty())
    {
        if (lang == QLocale::Language::AnyLanguage)
            name = QString(AUDIO_TRACK).arg(index + 1);
        else
            name = QLocale::languageToString(lang);
    }
    else
    {
        if (lang == QLocale::Language::AnyLanguage)
            name = title;
        else
            name = QString(AUDIO_TRACK_NAME).arg(title, QLocale::languageToString(lang));
    }
    
    return name;
}

void LeqiMenu::setAudioTrack(QAction* trackAction)
{
    if (actions.size() > 1)
    {
        emit menuAudioTrack(actions.indexOf(trackAction));
    }
}

void LeqiMenu::open()
{
    emit menuOpen();
}

void LeqiMenu::play()
{
    emit menuPlay();
}

void LeqiMenu::pause()
{
    emit menuPause();
}

void LeqiMenu::stop()
{
    emit menuStop();
}

void LeqiMenu::mute()
{
    emit menuMute();
}

void LeqiMenu::openHomePage()
{
    QDesktopServices::openUrl(QUrl(HOME_PAGE));
}

void LeqiMenu::showAboutDialog()
{
    QMessageBox::about(this, ACTION_ABOUT, ABOUT_CONTENT);
}

void LeqiMenu::quit()
{
    qApp->quit();
}
