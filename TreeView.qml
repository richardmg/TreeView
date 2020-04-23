import QtQuick 2.0
import Qt.labs.qmlmodels 1.0
import TreeView 2.15 as T

T.TreeView {
    id: control

    property real indent: 15
    property real columnPadding: 20
    property color bgColorOdd: "transparent"
    property color bgColorEven: "transparent"
    property color bgColorCurrent: Qt.rgba(0.8, 0.8, 0.8)

    delegate: DelegateChooser {
        DelegateChoice {
            // The column where the tree is at
            column: 0

            Rectangle {
                id: treeNode
                implicitWidth: treeNodeLabel.x + treeNodeLabel.width + (columnPadding / 2)
                implicitHeight: Math.max(treeNodeIndicator.height, treeNodeLabel.height)
                color: bgColor(column, row)
                //color: TreeView.bgColor

                property bool hasChildren: TreeView.hasChildren
                property bool isExpanded: TreeView.isExpanded

                Text {
                    id: treeNodeIndicator
                    x: control.depth(row) * indent
                    width: 15
                    text: hasChildren ? (isExpanded ? "▼" : "▶") : ""
                }

                Text {
                    id: treeNodeLabel
                    x: Math.max(treeNodeIndicator.x + treeNodeIndicator.width + 5, (control.depth(row) + 1) * indent)
                    text: display
                }

                MouseArea {
                    x: treeNodeIndicator.x
                    width: treeNodeIndicator.width
                    height: treeNodeIndicator.height
                    onClicked: {
                        if (hasChildren)
                            control.toggleExpanded(row)
                        else
                            control.currentViewIndex.row = row
                    }
                }
            }
        }

        DelegateChoice {
            //  All the other columns
            Rectangle {
                implicitWidth: infoLabel.x + infoLabel.width + (columnPadding / 2)
                color: bgColor(column, row)
                Text {
                    id: infoLabel
                    x: columnPadding / 2
                    text: display
                }
            }
        }
    }

    function bgColor(column, row) {
        if (treeView.currentViewIndex.row === row && treeView.currentViewIndex.column === column)
            return bgColorCurrent
        else if (row % 2)
            return bgColorOdd
        else
            return bgColorEven
    }
}
