#ifndef LEQISLIDER_H
#define LEQISLIDER_H

#include <QSlider>

class LeqiSlider : public QSlider
{
    Q_OBJECT

public:
    explicit LeqiSlider(QWidget *parent = nullptr);
    ~LeqiSlider();

protected:
    void enterEvent(QEnterEvent*) override;
    void leaveEvent(QEvent *) override;
    void mousePressEvent(QMouseEvent *) override;
    void keyPressEvent(QKeyEvent *) override;

signals:
    void seekPosition(int);
    void forwardFive();
    void backwardFive();

private:
    void initial();
};

#endif
