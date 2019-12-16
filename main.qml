import QtQuick 2.15
import QtQuick.Window 2.1
import TreeModel 1.0
import Qt.labs.qmlmodels 1.0

Window {
    id: root
    width: 800
    height: 600
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

            delegate: DelegateChooser {
                DelegateChoice {
                    column: 0 // the column where the tree is at
                    Rectangle {
                        implicitWidth: text.x + text.width
                        implicitHeight: text.height
                        color: "white"

                        Text {
                            id: text
                            x: _q_TreeView_ItemDepth * 20
                            text: {
                                if (_q_TreeView_HasChildren)
                                    var text = _q_TreeView_ItemExpanded ? "⬇" : "⮕"
                                text += "(icon) " + display
                            }
                        }

                        TapHandler {
                            onTapped: {
                                var modelIndex = modelAdaptor.mapRowToModelIndex(index)
                                if (modelAdaptor.isExpanded(modelIndex))
                                    modelAdaptor.collapse(modelIndex)
                                else
                                    modelAdaptor.expand(modelIndex)
                            }
                        }
                    }
                }
                DelegateChoice {
                    Rectangle {
                        implicitWidth: text2.width
                        implicitHeight: text2.height
                        color: "white"
                        Text {
                            id: text2
                            text: display
                        }
                    }
                }
            }

        }
    }
}
