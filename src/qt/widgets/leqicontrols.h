#ifndef LEQICONTROLS_H
#define LEQICONTROLS_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class LeqiButton;
class LeqiSlider;
QT_END_NAMESPACE

class LeqiControls : public QWidget
{
    Q_OBJECT

public:
    explicit LeqiControls(QWidget *parent = nullptr);
    ~LeqiControls();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private slots:
    void open();
    void play();
    void pause();
    void stop();
    void mute();
    void volume(int volume);
    void changeVoiceIcon(const QString &, const QString &);

signals:
    void controlOpen();
    void controlPlay();
    void controlPause();
    void controlStop();
    void controlMute();
    void controlVolume(int volume);
    void controlUp();
    void controlDown();

private:
    LeqiButton *voiceButton;
    LeqiSlider *volumeSlider;

    void initialControls();
};

#endif
