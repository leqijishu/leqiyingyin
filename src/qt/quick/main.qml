import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import QtMultimedia

ApplicationWindow {
    id: root
    width: 640
    height: 480
    visible: true
    title: qsTr("乐其影音")
    flags: Qt.Window | Qt.FramelessWindowHint

    Material.theme: Material.Dark
    Material.accent: Material.Purple

    property alias source: mediaPlayer.source

    MediaPlayer {
        id: mediaPlayer

        videoOutput: videoOutput
        audioOutput: AudioOutput {
            id: audio
            muted: false
            volume: 0.5
        }

        source: "d:/shipin/当男人恋爱时.mp4"
    }

    TitleBar {
        id: titleBar

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: videoOutput.top

        visible: !videoOutput.fullScreen

        mediaPlayer: mediaPlayer
        videoOutput: videoOutput

        onFullScreen: {
            parent.fullScreen ? showNormal() : showFullScreen()
            parent.fullScreen = !parent.fullScreen
        }

        onMinimizeWindow: root.showMinimized()
        onCloseWindow: root.close()
    }

    VideoOutput {
        id: videoOutput
        property bool fullScreen: false

        anchors.top: fullScreen ? parent.top : titleBar.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        TapHandler {
            onDoubleTapped: {
                parent.fullScreen ? showNormal() : showFullScreen()
                parent.fullScreen = !parent.fullScreen
            }
            onTapped: {
                switch (mediaPlayer.playbackState) {
                case MediaPlayer.PlayingState:
                    mediaPlayer.pause();
                    break;
                case MediaPlayer.PauseState:
                    mediaPlayer.play();
                    break;
                default:
                    mediaPlayer.play();
                    break;
                }
            }
        }
    }


}
