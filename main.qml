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

    TreeView {
        id: treeView
        anchors.fill: parent
        anchors.margins: 1
        model: fileSystemModel
        clip: true
        focus: true
        backgroundColorEvenRows: "white"
        backgroundColorOddRows: backgroundColorEvenRows
        navigationMode: TreeView.List

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
