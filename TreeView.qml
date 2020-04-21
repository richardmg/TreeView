import QtQuick 2.0
import Qt.labs.qmlmodels 1.0
import QtQuick.TreeView 2.15 as T

T.TreeView {
    id: treeView

    property real indent: 20
    property real columnSpacing: 10
    property color bgColorOdd: "transparent"
    property color bgColorEven: "transparent"

    property Component indicator: Text {
        width: implicitWidth + 5
        text: {
            if (treeView.hasChildren(row2))
                treeView.isExpanded(row2) ? "▼ " : "▶"
            else
                ""
        }
    }

    property Component label: Text {
        width: implicitWidth + 5
        text: display2
    }

    delegate: DelegateChooser {
        DelegateChoice {
            column: 0 // the column where the tree is at

            Rectangle {
                implicitWidth: indicatorLoader.x + indicatorLoader.width + labelLoader.width + columnSpacing
                implicitHeight: Math.max(indicatorLoader.height, labelLoader.height)
                color: row % 2 ? bgColorOdd : bgColorEven

                Loader {
                    id: indicatorLoader
                    x: treeView.depth(row) * indent
                    width: item.width
                    height: item.height
                    property int row2: row
                    sourceComponent: indicator
                }

                Loader {
                    id: labelLoader
                    x: (treeView.depth(row) + 1) * indent
                    width: item.width + columnSpacing
                    height: item.height
                    property int row2: row
                    property string display2: display
                    sourceComponent: label
                }

                MouseArea {
                    x: indicatorLoader.x
                    width: indicatorLoader.width
                    height: indicatorLoader.height
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
                implicitWidth: infoLoader.x + infoLoader.width
                color: row % 2 ? bgColorOdd : bgColorEven
                Loader {
                    id: infoLoader
                    x: columnSpacing
                    width: item.width
                    height: item.height
                    property int row2: row
                    property int column2: column
                    property string display2: display
                    sourceComponent: label
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
