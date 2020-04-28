import QtQuick 2.0
import Qt.labs.qmlmodels 1.0
import QtQuick.Shapes 1.0
import TreeView 2.15 as T

T.TreeView {
    id: control

    property real indent: 15
    property real columnPadding: 20

    // NB: The following properties are not a part of the TreeView API, and
    // only provided as a quick way to tweak _this_ style/delegate. Rather than
    // customising it the outside, consider just making a copy of the file to
    // create your own custom style.

    property color foregroundColorOddRows: "black"
    property color backgroundColorOddRows: "transparent"
    property color foregroundColorEvenRows: "black"
    property color backgroundColorEvenRows: "transparent"
    property color foregroundColorCurrent: "black"
    property color backgroundColorCurrent: "transparent"
    property color overlayColorCurrent: Qt.rgba(0, 0, 0, 0.5)
    property color expandedIndicatorColor: "black"

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
                    color: expandedIndicatorColor
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

    Shape {
        id: overlayShape
        z: 10
        property point currentPos: currentItem ? mapToItem(overlayShape, Qt.point(currentItem.x, currentItem.y)) : Qt.point(0, 0)
        visible: currentItem != null && overlayColorCurrent != "transparent"

        ShapePath {
            id: path
            fillColor: "transparent"
            strokeColor: overlayColorCurrent
            strokeWidth: 1
            strokeStyle: ShapePath.DashLine
            dashPattern: [1, 2]
            startX: currentItem ? currentItem.x + strokeWidth : 0
            startY: currentItem ? currentItem.y + strokeWidth : 0
            //onStartXChanged: print("startx:", startX)
            property real endX: currentItem ? currentItem.width + startX - (strokeWidth * 2) : 0
            property real endY: currentItem ? currentItem.height + startY - (strokeWidth * 2) : 0
            PathLine { x: path.endX; y: path.startY }
            PathLine { x: path.endX; y: path.endY }
            PathLine { x: path.startX; y: path.endY }
            PathLine { x: path.startX; y: path.startY }
        }
    }

    function bgColor(column, row) {
        if (navigationMode === TreeView.List && currentViewIndex.row === row)
            return backgroundColorCurrent
        else if (navigationMode === TreeView.Table && currentViewIndex === viewIndex(column, row))
            return backgroundColorCurrent
        else if (row % 2)
            return backgroundColorOddRows
        else
            return backgroundColorEvenRows
    }

    function fgColor(column, row) {
        if (navigationMode === TreeView.List && currentViewIndex.row === row)
            return foregroundColorCurrent
        else if (navigationMode === TreeView.Table && currentViewIndex === viewIndex(column, row))
            return foregroundColorCurrent
        else if (row % 2)
            return foregroundColorOddRows
        else
            return foregroundColorEvenRows
    }
}
