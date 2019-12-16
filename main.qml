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

            function isRowExpanded(row)
            {
                return modelAdaptor.isExpanded(row);
            }

            function setRowExpanded(row, expanded)
            {
                var modelIndex = modelAdaptor.mapRowToModelIndex(row)
                if (expanded)
                    modelAdaptor.expand(modelIndex)
                else
                    modelAdaptor.collapse(modelIndex)
            }

            function toggleRowExpanded(row)
            {
                setRowExpanded(row, !isRowExpanded(row))
            }

            function depth(row)
            {
                return modelAdaptor.depthAtRow(row)
            }

            function hasChildren(row)
            {
                return modelAdaptor.hasChildren(row)
            }

            function hasSiblings(row)
            {
                return modelAdaptor.hasSiblings(row)
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
                            x: treeView.depth(row) * 20
                            text: {
                                var text = "";
                                if (treeView.hasChildren(row))
                                    text += treeView.isRowExpanded(row) ? "⬇" : "⮕"
                                text += display
                            }
                        }

                        TapHandler {
                            onTapped: treeView.toggleRowExpanded(row)
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
