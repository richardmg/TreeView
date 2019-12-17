import QtQuick 2.15
import QtQuick.Window 2.1
import Qt.labs.qmlmodels 1.0

import TreeView 2.15

Window {
    id: root
    width: 800
    height: 600
    visible: true
    visibility: Window.AutomaticVisibility

    property var selectedIndex
    property int margins: 2

    function selectRow(row)
    {
        selectedIndex = treeView.modelIndex(row, 0)
    }

    function bgColor(row) {
        if (treeView.modelIndex(row, 0) === selectedIndex)
            return Qt.rgba(0.9, 1, 0.9, 1)
        else if (row % 2)
            return Qt.rgba(0.8, 0.8, 1, 1)
        else
            return Qt.rgba(0.9, 0.9, 1, 1)
    }

    Rectangle {
        anchors.fill: parent
        anchors.margins: 10
        color: Qt.rgba(0.9, 0.9, 0.9, 1)

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
                        color: bgColor(row)

                        Text {
                            id: text
                            x: treeView.depth(row) * 20
                            text: {
                                var text = "";
                                if (treeView.hasChildren(row))
                                    text += treeView.isExpanded(row) ? "▼ " : "▶ "
                                text += display
                            }

                            MouseArea {
                                anchors.fill: parent
                                onClicked: {
                                    if (treeView.hasChildren(row))
                                        treeView.toggleExpanded(row)
                                    else
                                       selectRow(row)
                                }
                            }
                        }

                        TapHandler {
                            onTapped: selectRow(row)
                        }
                    }
                }

                DelegateChoice {
                    Rectangle {
                        implicitWidth: text2.width
                        implicitHeight: text2.height
                        color: bgColor(row)
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
