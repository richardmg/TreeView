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
        color: "black"//Qt.rgba(0.9, 0.9, 0.9, 1)

        TreeView {
            id: treeView
            anchors.fill: parent
            anchors.margins: 2
            model: fileSystemModel
            clip: true
            focus: true
            rowSpacing: 1
            columnSpacing: 1
            bgColorEven: "white"
            bgColorOdd: bgColorEven
            Keys.onReturnPressed: {
                var index = modelIndex(currentRow, 0);
                var label = model.data(index, treeView.textRole)
                print("selected:", label)
            }
        }
    }
}
