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

                Text {
                    id: indicator
                    x: treeView.depth(row) * 20
                    text: {
                        if (treeView.hasChildren(row))
                            treeView.isExpanded(row) ? "▼" : "▶"
                        else
                            ""
                    }
                }

                Text {
                    id: text
                    anchors.left: indicator.right
                    anchors.leftMargin: 5
                    text: display
                }

                MouseArea {
                    anchors.fill: indicator
                    onClicked: {
                        if (treeView.hasChildren(row))
                            treeView.toggleExpanded(row)
                        else
                            treeView.currentRow = row
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

            }
        }
    }

    function bgColor(row) {
        if (row === treeView.currentRow)
            return Qt.rgba(0.9, 1, 0.9, 1)
        else if (row % 2 && treeView.alternatingRowColors)
            return Qt.rgba(0.8, 0.8, 1, 1)
        else
            return Qt.rgba(0.9, 0.9, 1, 1)
    }
}
