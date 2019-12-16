import QtQuick 2.15
import QtQuick.Window 2.1
import TreeModel 1.0

Window {
    id: root
    width: 480
    height: 640
    visible: true
    visibility: Window.AutomaticVisibility

    property int margins: 2

    TreeModel {
        id: treeModel
    }

    TreeToTableModel {
        id: treeToTableModel
        sourceModel: treeModel
    }

    TreeModelAdaptor {
        id: modelAdaptor
        model: treeModel
    }

    Rectangle {
        anchors.fill: parent
        anchors.margins: 10
        color: "lightgray"

        TableView {
            anchors.fill: parent
            anchors.margins: root.margins
            model: modelAdaptor
            columnSpacing: root.margins

            delegate: Rectangle {
                implicitWidth: text.x + text.width
                implicitHeight: text.height
                color: "white"

                Text {
                    id: text
                    x: _q_TreeView_ItemDepth * 20
                    text: {
                        var modelIndex = modelAdaptor.mapRowToModelIndex(index)

                        let text = ""
                        if (_q_TreeView_HasChildren)
                            text += _q_TreeView_ItemExpanded ? "⬇" : "⮕"

                        text += "(icon) " + display
                    }
                }

                MouseArea {
                    // Use pointer handlers
                    anchors.fill: parent
                    onClicked: {
                        var modelIndex = modelAdaptor.mapRowToModelIndex(index)
                        if (modelAdaptor.isExpanded(modelIndex))
                            modelAdaptor.collapse(modelIndex)
                        else
                            modelAdaptor.expand(modelIndex)
                    }
                }
            }

        }
    }
}
