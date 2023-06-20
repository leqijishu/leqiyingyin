#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QString>
#include <QObject>

const QString APP_NAME = QObject::tr("乐其影音");
const QString TIP_APPMENU = QObject::tr("主菜单");
const QString TIP_FULLSCREEN = QObject::tr("全屏");
const QString TIP_MINIMIZE = QObject::tr("最小化");
const QString TIP_CLOSE = QObject::tr("关闭");
const QString TIP_OPEN = QObject::tr("打开文件");
const QString TIP_PLAY = QObject::tr("播放");
const QString TIP_PAUSE = QObject::tr("暂停");
const QString TIP_STOP = QObject::tr("停止");
const QString TIP_MUTE = QObject::tr("静音");
const QString TIP_CANCEL_MUTE = QObject::tr("取消静音");
const QString TIP_ONTOP = QObject::tr("置顶");

const QString ACTION_OPEN = QObject::tr("打开文件…");
const QString ACTION_AUDIO_TRACKS = QObject::tr("音轨");
const QString ACTION_HELP = QObject::tr("帮助");
const QString ACTION_HOME = QObject::tr("主页");
const QString ACTION_ABOUT = QObject::tr("关于…");
const QString ACTION_QUIT = QObject::tr("退出");

const QString AUDIO_TRACK_PTH = QObject::tr("普通话");
const QString AUDIO_TRACK_GY = QObject::tr("国语");
const QString AUDIO_TRACK = QObject::tr("音轨 %1");
const QString AUDIO_TRACK_NAME = QObject::tr("%1 - [%2]");

const QString HOME_PAGE = QObject::tr("https://gitee.com/leqijishu/leqiyingyin");
const QString ABOUT_CONTENT = QObject::tr("乐其影音是一款基于Qt的开源免费软件\n\
欢迎大家在软件主页提出反馈和宝贵意见。\n\
乐其技术\n\
乐于创造，乐于分享，乐在其中");

const QString LABEL_DURATION = QObject::tr("00:00:00 / 00:00:00");

#endif
