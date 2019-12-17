import QtQuick 2.15
import QtQuick.Window 2.1

Window {
    id: root
    width: 800
    height: 600
    visible: true
    visibility: Window.AutomaticVisibility

    Rectangle {
        anchors.fill: parent
        anchors.margins: 10
        color: Qt.rgba(0.9, 0.9, 0.9, 1)

        TreeView {
            id: treeView
            anchors.fill: parent
            anchors.margins: 2
            model: fileSystemModel
            columnSpacing: 2
            clip: true
        }
    }
}
