#include "leqiyingyin.h"
#include "constants.h"

#include <QApplication>
#include <QVideoWidget>
#include <QMediaPlayer>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QCoreApplication::setApplicationName(APP_NAME);
    
    LeqiYingYin leqiYingYin;
    leqiYingYin.show();

    return app.exec();
}