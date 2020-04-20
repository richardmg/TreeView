import QtQuick 2.0
import Qt.labs.qmlmodels 1.0
import QtQuick.TreeView 2.15 as T

T.TreeView {
    id: treeView

    delegate: DelegateChooser {
        DelegateChoice {
            column: 0 // the column where the tree is at

            Rectangle {
                implicitWidth: text.x + text.width
                implicitHeight: text.height
                color: bgColor(row)

                MouseArea {
                    anchors.fill: parent
                    onClicked: treeView.currentRow = row
                }

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
                                treeView.currentRow = row
                        }
                    }
                }
            }
        }

        DelegateChoice {
            Rectangle {
                implicitWidth: text2.width + 20
                implicitHeight: text2.height
                color: bgColor(row)
                Text {
                    id: text2
                    x: 10
                    text: display
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: treeView.currentRow = row;
                }
            }
        }
    }

    function bgColor(row) {
        if (row === treeView.currentRow)
            return Qt.rgba(0.9, 1, 0.9, 1)
        else if (row % 2)
            return Qt.rgba(0.8, 0.8, 1, 1)
        else
            return Qt.rgba(0.9, 0.9, 1, 1)
    }
}
