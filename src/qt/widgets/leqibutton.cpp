#include "leqibutton.h"

#include <QEvent>
#include <QKeyEvent>

LeqiButton::LeqiButton(QWidget *parent)
    : QPushButton(parent)
{
    setFocusPolicy(Qt::NoFocus);
}

LeqiButton::LeqiButton(const QString &toolTip, QWidget *parent)
    : QPushButton(parent)
{
    setToolTip(toolTip);
    setFocusPolicy(Qt::NoFocus);
}

LeqiButton::LeqiButton(const QString &toolTip, const QString &objectName, QWidget *parent)
    : QPushButton(parent)
{
    setToolTip(toolTip);
    setObjectName(objectName);
    setFocusPolicy(Qt::NoFocus);
}

LeqiButton::LeqiButton(const QString &toolTip, const QString &objectName
                        , const QString &text, QWidget *parent)
    : QPushButton(parent)
{
    setToolTip(toolTip);
    setObjectName(objectName);
    setText(text);
    setFocusPolicy(Qt::NoFocus);
}

LeqiButton::~LeqiButton()
{}
