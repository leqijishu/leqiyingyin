#ifndef LEQIYINGYIN_H
#define LEQIYINGYIN_H

#include <QWidget>
#include <QDir>
#include <QStringLiteral>

QT_BEGIN_NAMESPACE
class QMediaPlayer;
class QAudioOutput;
class QHBoxLayout;
class QSlider;
class QLabel;
class QPoint;
class LeqiTitleBar;
class LeqiButton;
class LeqiVideoWidget;
class LeqiControlBar;
class QMediaMetaData;
QT_END_NAMESPACE

class LeqiYingYin : public QWidget
{
    Q_OBJECT

public:
    explicit LeqiYingYin(QWidget *parent = nullptr);
    ~LeqiYingYin();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private slots:
    void openFile();
    void stopPlaying();
    void setPosition(int position);
    void positionChanged(qint64 position);
    void durationChanged(qint64 duration);
    void toggleFullScreen();
    void togglePauseOrPlay();
    void toggleMute();
    void setVolume(int value);
    void tracksChanged();
    void setAudioTrack(int);
    void forwardFive();
    void backwardFive();
    void volumeUp();
    void volumeDown();

signals:
    void setTitle(const QString &title);
    void setRange(int min, int max);
    void setDuration(const QString &duration);
    void setVoiceIcon(const QString &, const QString &);
    void setAudioTracks(const QList<QMediaMetaData>&);

private:
    QMediaPlayer *player;
    LeqiVideoWidget *leqiVideoWidget;
    QAudioOutput *audioOutput;
    QSize mainWindowSize;
    LeqiButton *playButton;
    QSlider *positionSlider;
    LeqiButton *leqiButton;
    QLabel *labelDuration;
    qint64 nDuration;
    QPoint clickPosition;
    LeqiTitleBar *leqiTitleBar;
    LeqiControlBar *leqiControlBar;
    QString defaultDir;

    void initMainWindow();
    LeqiTitleBar *createTitleBar();
    LeqiVideoWidget *createVideoWidget();
    LeqiControlBar *createControlBar();
    QHBoxLayout *createDurationLayout();
    QHBoxLayout *createControlLayout();
    QHBoxLayout *createButtonsLayout();
    void pauseOrPlay();
    void updateDurationInfo(qint64 currentInfo);
    void loadStyleSheet(const QString &sheetName);
    void readSettings();
    void saveSettings();
    void saveSettings(const QString &group, const QString &key, const QString &value);
    void setDefaultDir();
    void resetSizes();
    void playVideo(const QString&);

    const QString settingsName = "/data/settings.ini";
};
#endif
