import QtQuick 2.15
import QtQuick.Window 2.1
import Qt.labs.qmlmodels 1.0

import TreeView 1.0

Window {
    id: root
    width: 800
    height: 600
    visible: true
    visibility: Window.AutomaticVisibility

    property int margins: 2

    Rectangle {
        anchors.fill: parent
        anchors.margins: 10
        color: "lightgray"

        TreeView {
            id: treeView
            anchors.fill: parent
            anchors.margins: root.margins
            model: fileSystemModel
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
                            x: treeView.depth(row) * 20
                            text: {
                                var text = "";
                                if (treeView.hasChildren(row))
                                    text += treeView.isExpanded(row) ? "⬇" : "⮕"
                                text += display
                            }
                        }

                        TapHandler {
                            onTapped: treeView.toggleExpanded(row)
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
