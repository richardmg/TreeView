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

            indicator: Text {
                width: implicitWidth
                text: hasChildren ? (isExpanded ? "[-]xxxxx" : "[+]") : ""
            }

            Keys.onReturnPressed: {
                var modelIndex = mapToModel(currentViewIndex);
                var label = model.data(modelIndex, treeView.textRole)
                print("selected:", label)
            }

            Keys.onTabPressed: {
                var rootIndex = fileSystemModel.index(0, 0)
                var parentIndex = fileSystemModel.index(1, 0, rootIndex)
                var childIndex = fileSystemModel.index(10, 0, parentIndex)

                var childIndexView = mapFromModel(childIndex)
                print(childIndexView.row)
                currentViewIndex = childIndexView
            }
        }
    }
}
