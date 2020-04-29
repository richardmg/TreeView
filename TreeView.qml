import QtQuick 2.0
import Qt.labs.qmlmodels 1.0
import QtQuick.Shapes 1.0
import QtQuick.Templates 2.12 as T
import TreeView 2.15 as T

T.TreeView {
    id: control

    property QtObject styleHints: QtObject {
        // Note: if you need to tweak the style beyond the styleHints, just
        // copy this file into your project and use it as a starting point
        // for creating your own custom version.
        property real indent: 15
        property real columnPadding: 20
        property color foregroundOdd: "black"
        property color backgroundOdd: "transparent"
        property color foregroundEven: "black"
        property color backgroundEven: "transparent"
        property color foregroundCurrent: navigationMode === TreeView.List ? "white" : "transparent"
        property color backgroundCurrent: navigationMode === TreeView.List ? "#1E8AE9" : "transparent"
        property color overlay: Qt.rgba(0, 0, 0, 0.5)
        property color indicator: "black"
    }

    function bgColor(column, row) {
        if (currentIndex.row === row)
            return backgroundCurrent
        else if (row % 2)
            return backgroundOdd
        else
            return backgroundEven
    }

    function fgColor(column, row) {
        if (currentIndex.row === row)
            return foregroundCurrent
        else if (row % 2)
            return foregroundOdd
        else
            return foregroundEven
    }

    delegate: DelegateChooser {
        DelegateChoice {
            // The column where the tree is drawn
            column: 0

            Rectangle {
                id: treeNode
                implicitWidth: treeNodeLabel.x + treeNodeLabel.width + (columnPadding / 2)
                implicitHeight: Math.max(treeNodeIndicator.height, treeNodeLabel.height)
                color: bgColor(column, row)

                property bool hasChildren: TreeView.hasChildren
                property bool isExpanded: TreeView.isExpanded
                property int depth: TreeView.depth

                Text {
                    id: treeNodeIndicator
                    x: depth * indent
                    width: 15
                    color: "black"
                    text: hasChildren ? (isExpanded ? "▼" : "▶") : ""
                }

                Text {
                    id: treeNodeLabel
                    x: treeNodeIndicator.x + indent
                    clip: true
                    color: fgColor(column, row)
                    text: model.display
                }

                MouseArea {
                    x: treeNodeIndicator.x
                    width: treeNodeIndicator.width
                    height: treeNodeIndicator.height
                    onClicked: {
                        if (hasChildren)
                            control.toggleExpanded(row)
                        else
                            control.currentIndex.row = row
                    }
                }
            }
        }

        DelegateChoice {
            //  The remaining columns after the tree column will use this delegate
            Rectangle {
                implicitWidth: infoLabel.x + infoLabel.width + (columnPadding / 2)
                color: bgColor(column, row)
                Text {
                    id: infoLabel
                    x: columnPadding / 2
                    color: fgColor(column, row)
                    text: display
                    clip: true
                }

            }
        }
    }

    Shape {
        id: overlayShape
        z: 10
        property point currentPos: currentItem ? mapToItem(overlayShape, Qt.point(currentItem.x, currentItem.y)) : Qt.point(0, 0)
        visible: currentItem != null

        ShapePath {
            id: path
            fillColor: "transparent"
            strokeColor: Qt.rgba(0, 0, 0, 0.5)
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

}
