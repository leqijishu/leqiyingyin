#include "leqislider.h"

#include <QMouseEvent>
#include <QCursor>
#include <QMessageBox>
#include <QApplication>

LeqiSlider::LeqiSlider(QWidget *parent)
    : QSlider(parent)
{
    initial();
}

LeqiSlider::~LeqiSlider()
{}

void LeqiSlider::enterEvent(QEnterEvent *event)
{
    setStyleSheet("::handle:horizontal { \
                    background: rgb(198, 198, 198); \
                    width: 12px; \
                    margin: -3px 0px; \
                    border-radius: 6px; \
                    }");
}

void LeqiSlider::leaveEvent(QEvent *event)
{
    setStyleSheet("::handle:horizontal{}");
}

void LeqiSlider::mousePressEvent(QMouseEvent *event)
{
    switch (event->button()) {
    case Qt::LeftButton:
    {
        int currentX = event->pos().x();
        qreal per = currentX * 1.0 / width();
        int value = per * (maximum() - minimum()) + minimum();
        setValue(value);
        emit seekPosition(value);
        event->accept();
    }
        break;
    default:
        QSlider::mousePressEvent(event);
        break;
    }
}

void LeqiSlider::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Right:
        QApplication::activeWindow();
        setFocus();
        emit forwardFive();
        event->accept();
        break;
    case Qt::Key_Left:
        QApplication::activeWindow();
        setFocus();
        emit backwardFive();
        event->accept();
        break;
    case Qt::Key_Up:
    case Qt::Key_Down:
        break;
    default:
        QSlider::keyPressEvent(event);
        break;
    }
}

void LeqiSlider::initial()
{
    setOrientation(Qt::Horizontal);
}
