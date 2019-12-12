import QtQuick 2.15
import QtQuick.Window 2.1
import TreeModel 1.0

Window {
    width: 480
    height: 640
    visible: true
    visibility: Window.AutomaticVisibility

    TreeModel {
        id: treeModel
    }

    TableView {
        anchors.fill: parent
        model: treeModel
        delegate: Text { text: "(" + column + ", " + row + ")"; }
    }
}
