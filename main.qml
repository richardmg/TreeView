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

    TreeModelAdaptor {
        id: modelAdaptor
        model: fileSystemModel
    }

    Rectangle {
        anchors.fill: parent
        anchors.margins: 10
        color: "lightgray"

        TableView {
            id: treeView
            anchors.fill: parent
            anchors.margins: root.margins
            model: modelAdaptor
            columnSpacing: root.margins

            function isExpanded(index)
            {
                var modelIndex = modelAdaptor.mapRowToModelIndex(index)
                return modelAdaptor.isExpanded(modelIndex);
            }

            function setExpanded(index, expanded)
            {
                var modelIndex = modelAdaptor.mapRowToModelIndex(index)
                if (expanded)
                    modelAdaptor.expand(modelIndex)
                else
                    modelAdaptor.collapse(modelIndex)
            }

            function toggleExpanded(index)
            {
                setExpanded(index, !isExpanded(index))
            }

            function depthForIndex(index)
            {

            }

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
                                text += display
                            }
                        }

                        TapHandler {
                            onTapped: treeView.toggleExpanded(index)
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
