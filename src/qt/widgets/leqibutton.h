#ifndef LEQIBUTTON_H
#define LEQIBUTTON_H

#include <QPushButton>

class LeqiButton : public QPushButton
{
    Q_OBJECT

public:
    explicit LeqiButton(QWidget *parent = nullptr);
    explicit LeqiButton(const QString &toolTip, QWidget *parent = nullptr);
    explicit LeqiButton(const QString &toolTip, const QString &objectName, QWidget *parent = nullptr);
    explicit LeqiButton(const QString &toolTip, const QString &text,
                        const QString &objectName, QWidget *parent = nullptr);
    ~LeqiButton();
};

#endif
