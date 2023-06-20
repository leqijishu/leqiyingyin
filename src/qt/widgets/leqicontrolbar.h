#ifndef LEQICONTROLBAR_H
#define LEQICONTROLBAR_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QSlider;
class QLabel;
class QHBoxLayout;
QT_END_NAMESPACE

class LeqiControlBar : public QWidget
{
    Q_OBJECT

public:
    explicit LeqiControlBar(QWidget *parent = nullptr);
    ~LeqiControlBar();

    void setValue(int value);
    void setRange(int min, int max);

private slots:
    void open();
    void play();
    void pause();
    void stop();
    void mute();
    void volume(int volume);
    void setPositionRange(int min, int max);
    void setDuration(const QString &duration);
    void setPosition(int position);
    void setVoiceIcon(const QString &, const QString &);
    void forwardFive();
    void backwardFive();
    void up();
    void down();
    void setFullScreen(bool);

signals:
    void barOpen();
    void barPlay();
    void barPause();
    void barStop();
    void barMute();
    void barVolume(int);
    void barPosition(int);
    void changeVoiceIcon(const QString &, const QString);
    void barForwardFive();
    void barBackwardFive();
    void barUp();
    void barDown();

private:
    QSlider *positionSlider;
    QLabel *labelDuration;
    bool isFullScreen;

    void initialControlBar();
    QHBoxLayout *createDurationLayout();
};

#endif
