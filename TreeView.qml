import QtQuick 2.0
import Qt.labs.qmlmodels 1.0
import QtQuick.TreeView 2.15 as T

T.TreeView {
    id: control

    property real indent: 15
    property real columnSpacing: 10
    property color bgColorOdd: "transparent"
    property color bgColorEven: "transparent"
    property color bgColorCurrent: Qt.rgba(0.8, 0.8, 0.8)

    property Component indicator: Text {
        width: implicitWidth
        text: {
            if (control.hasChildren(row2))
                control.isExpanded(row2) ? "▼" : "▶"
            else
                ""
        }
    }

    property Component treeLabel: Text {
        text: display2
    }

    property Component infoLabel: Text {
        text: display2
    }

    delegate: DelegateChooser {
        DelegateChoice {
            // The column where the tree is at
            column: 0

            Rectangle {
                implicitWidth: labelLoader.x + indicatorLoader.width + labelLoader.width + columnSpacing
                implicitHeight: Math.max(indicatorLoader.height, labelLoader.height)
                color: bgColor(row)

                Loader {
                    id: indicatorLoader
                    x: control.depth(row) * indent
                    property int row2: row
                    sourceComponent: indicator
                }

                Loader {
                    id: labelLoader
                    x: Math.max(indicatorLoader.x + indicatorLoader.width + 5, (control.depth(row) + 1) * indent)
                    property int row2: row
                    property string display2: display
                    sourceComponent: treeLabel
                }

                MouseArea {
                    x: indicatorLoader.x
                    width: indicatorLoader.width
                    height: indicatorLoader.height
                    onClicked: {
                        if (control.hasChildren(row))
                            control.toggleExpanded(row)
                        else
                            control.currentRow = row
                    }
                }
            }
        }

        DelegateChoice {
            //  All the other columns
            Rectangle {
                implicitWidth: infoLoader.x + infoLoader.width
                color: bgColor(row)
                Loader {
                    id: infoLoader
                    x: columnSpacing
                    property int row2: row
                    property int column2: column
                    property string display2: display
                    sourceComponent: infoLabel
                }
            }
        }
    }

    function bgColor(row) {
        if (treeView.currentRow === row)
            return bgColorCurrent
        else if (row % 2)
            return bgColorOdd
        else
            return bgColorEven
    }
}
