import QtQuick 2.0
import Qt.labs.qmlmodels 1.0
import TreeView 2.15 as T

T.TreeView {
    id: control

    property real indent: 15
    property real columnPadding: 20

    property color backgroundColorOddRows: "transparent"
    property color backgroundColorEvenRows: "transparent"
    property color backgroundColorCurrentIndex: Qt.rgba(0.8, 0.8, 0.8)
    property color foregroundColorOddRows: "black"
    property color foregroundColorEvenRows: "black"
    property color foregroundColorCurrentIndex: "red"
    property color accentColor: "black"

    delegate: DelegateChooser {
        DelegateChoice {
            // The column where the tree is at
            column: 0

            Rectangle {
                id: treeNode
                implicitWidth: treeNodeLabel.x + treeNodeLabel.width + (columnPadding / 2)
                implicitHeight: Math.max(treeNodeIndicator.height, treeNodeLabel.height)
                color: bgColor(column, row)

                property bool hasChildren: TreeView.hasChildren
                property bool isExpanded: TreeView.isExpanded

                Text {
                    id: treeNodeIndicator
                    x: control.depth(row) * indent
                    width: 15
                    color: accentColor
                    text: hasChildren ? (isExpanded ? "▼" : "▶") : ""
                }

                Text {
                    id: treeNodeLabel
                    x: Math.max(treeNodeIndicator.x + treeNodeIndicator.width + 5, (control.depth(row) + 1) * indent)
                    color: fgColor(column, row)
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
                    color: fgColor(column, row)
                    text: display
                }
            }
        }
    }

    function bgColor(column, row) {
        if (navigationMode === TreeView.List && currentViewIndex.row === row)
            return backgroundColorCurrentIndex
        else if (navigationMode === TreeView.Table && currentViewIndex === viewIndex(column, row))
            return backgroundColorCurrentIndex
        else if (row % 2)
            return backgroundColorOddRows
        else
            return backgroundColorEvenRows
    }

    function fgColor(column, row) {
        if (navigationMode === TreeView.List && currentViewIndex.row === row)
            return foregroundColorCurrentIndex
        else if (navigationMode === TreeView.Table && currentViewIndex === viewIndex(column, row))
            return foregroundColorCurrentIndex
        else if (row % 2)
            return foregroundColorOddRows
        else
            return foregroundColorEvenRows
    }
}
