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

    TreeToTableModel {
        id: treeToTableModel
        sourceModel: treeModel
    }

    TreeModelAdaptor {
        id: modelAdaptor
        model: treeModel
    }

    TableView {
        anchors.fill: parent
        model: modelAdaptor
        delegate: Item {
            implicitWidth: text.x + text.width
            implicitHeight: text.height
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
