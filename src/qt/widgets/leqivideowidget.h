#ifndef LEQIVIDEOWIDGET_H
#define LEQIVIDEOWIDGET_H

#include <QVideoWidget>
#include <QMediaMetaData>

QT_BEGIN_NAMESPACE
class LeqiMenu;
QT_END_NAMESPACE

class LeqiVideoWidget : public QVideoWidget
{
    Q_OBJECT

public:
    explicit LeqiVideoWidget(QWidget *parent = nullptr);
    ~LeqiVideoWidget();

    void setSource(const QString &source);

protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void setAudioTracksMenu(const QList<QMediaMetaData>&);
    void setAudioTrack(int);
    void open();
    void play();
    void pause();
    void stop();
    void mute();

signals:
    void togglePauseOrPlay();
    void openFile();
    void createAudioTracksMenu(const QList<QMediaMetaData>&);
    void videoAudioTrack(int);
    void videoOpen();
    void videoPlay();
    void videoPause();
    void videoStop();
    void videoMute();
    void videoForwardFive();
    void videoBackwardFive();

private:
    QString source;
    LeqiMenu *leqiMenu;

    void initialMenu();
};
#endif
