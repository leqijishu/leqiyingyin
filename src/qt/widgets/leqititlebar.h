#ifndef LEQITITLEBAR_H
#define LEQITITLEBAR_H

#include <QWidget>
#include <QLabel>

QT_BEGIN_NAMESPACE
class QMediaMetaData;
class LeqiMenu;
QT_END_NAMESPACE

class LeqiTitleBar : public QWidget
{
    Q_OBJECT

public:
    explicit LeqiTitleBar(QWidget *parent = nullptr);
    ~LeqiTitleBar();

protected:
    void enterEvent(QEnterEvent *) override;
    void leaveEvent(QEvent *) override;

private slots:
    void toggleFullScreen();
    void showMinimized();
    void close();
    void setTitle(const QString &title);
    void setAudioTracksMenu(const QList<QMediaMetaData>&);
    void setAudioTrack(int);
    void open();
    void play();
    void pause();
    void stop();
    void mute();
    void setFullScreen(bool);

signals:
    void fullScreen();
    void minimizeWindow();
    void closeWindow();
    void createAudioTracksMenu(const QList<QMediaMetaData>&);
    void titleBarAudioTrack(int);
    void titleBarOpen();
    void titleBarPlay();
    void titleBarPause();
    void titleBarStop();
    void titleBarMute();

private:
    QLabel *labelTitle;
    LeqiMenu *leqiMenu;
    bool isFullScreen;

    void initialTitleBar();
};

#endif
