import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import QtQuick.Layouts
import QtQuick.Controls.Material
import QtMultimedia

Item {
    id: root

    Material.theme: Material.Dark
    Material.foreground: Material.Grey

    required property MediaPlayer mediaPlayer
    required property VideoOutput videoOutput

    height: frame.height

    signal fullScreen
    signal minimizeWindow
    signal closeWindow

    function loadUrl(url) {
        mediaPlayer.stop()
        mediaPlayer.source = url
        mediaPlayer.play()
    }

    FileDialog {
        id: fileDialog
        title: "选择文件"
        onAccepted: {
            mediaPlayer.stop()
            mediaPlayer.source = fileDialog.currentFile
            videoName = fileDialog.currentFile
            mediaPlayer.play()
        }
    }

    Rectangle {
        id: frame
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.top

        Button {
            id: leqiButton
            icon.source: "/resources/logo/logo32.png"
            text: "乐其影音"
            flat: true
            Material.foreground: Material.Purple
        }

        Label {
            id: videoName
            anchors.centerIn: parent
        }

        Button {
            id: fullScreenButton
            text: "全屏"
            anchors.right: minimizeButton.left
            flat: true
            onClicked: fullScreen()
        }

        Button {
            id: minimizeButton
            text: "最小化"
            anchors.right: closeButton.left
            flat: true
            onClicked: minimizeWindow()
        }

        Button {
            id: closeButton
            text: "关闭"
            anchors.right: parent.right
            flat: true
            onClicked: closeWindow()
        }
    }
}
