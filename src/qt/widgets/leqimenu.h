#ifndef LEQIMENU_H
#define LEQIMENU_H

#include <QMenu>
#include <QMediaMetaData>

class LeqiMenu : public QMenu
{
    Q_OBJECT

public:
    explicit LeqiMenu(QWidget *parent = nullptr);
    ~LeqiMenu();

private slots:
    void createAudioTracksMenu(const QList<QMediaMetaData> &);
    void setAudioTrack(QAction*);
    void open();
    void play();
    void pause();
    void stop();
    void mute();
    void openHomePage();
    void showAboutDialog();
    void quit();

signals:
    void menuAudioTrack(int);
    void menuOpen();
    void menuPlay();
    void menuPause();
    void menuStop();
    void menuMute();

private:
    QMenu *audioTracksMenu;
    QVector<QAction*> actions;

    void initialMenu();
    QString trackName(const QMediaMetaData &, int);
};

#endif