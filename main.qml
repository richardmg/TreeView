import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.1
import Qt.labs.qmlmodels 1.0

Window {
    id: root
    width: 800
    height: 600
    visible: true
    visibility: Window.AutomaticVisibility

    Row {
        id: controlRow
        CheckBox {
            id: configured
            text: "Configured"
        }
    }

    TreeView {
        id: treeView
        anchors.top: controlRow.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 20
        model: fileSystemModel
        clip: true
        focus: true
        navigationMode: TreeView.List

        states: State {
            when: configured.checked
            PropertyChanges {
                target: treeView
                navigationMode: TreeView.Table
                styleHints.indent: 15
                styleHints.columnPadding: 20
                styleHints.font.bold: true
                styleHints.foregroundOdd: "#001a66"
                styleHints.backgroundOdd: "#e6ecff"
                styleHints.foregroundEven: "#001a66"
                styleHints.backgroundEven: "#ccd9ff"
                styleHints.foregroundCurrent: "#ebf0fa"
                styleHints.backgroundCurrent: "#2e5cb8"
                styleHints.indicator: "#000d33"
                styleHints.overlay: navigationMode === TreeView.Table ? Qt.rgba(1, 1, 1) : "transparent"
            }
        }

        Keys.onReturnPressed: {
            var label = model.data(currentModelIndex, treeView.textRole)
            print("selected row", currentIndex.row + ", label:", label)
        }

        Keys.onTabPressed: {
            // Set the second file inside the root folder as current:
            var rootIndex = fileSystemModel.index(0, 0)
            var childIndex = fileSystemModel.index(1, 0, rootIndex)
            currentViewIndex = mapFromModel(childIndex)
        }
    }
}
