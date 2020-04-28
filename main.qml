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

    HorizontalHeaderView {
        id: header
        syncView: treeView
        //Component.onCompleted: print(model.headerData(0, Qt.Horizontal))
    }

    TreeView {
        id: treeView
        anchors.top: header.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 1
        model: fileSystemModel
        clip: true
        focus: true
        backgroundColorEvenRows: "white"
        backgroundColorOddRows: backgroundColorEvenRows
        navigationMode: TreeView.Table

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
