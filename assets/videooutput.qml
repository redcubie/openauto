import QtQuick 2.3
import QtQuick.Window 2.15
import QtMultimedia 5.15

Window {
    objectName: "window"
    color: "red"
    flags: Qt.Window | Qt.FramelessWindowHint

    MediaPlayer {
        id: player
        objectName: "player"
    }

    VideoOutput {
        id: output
        source: player
        anchors.fill: parent
    }
}
