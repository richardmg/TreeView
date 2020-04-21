import QtQuick 2.0
import Qt.labs.qmlmodels 1.0
import QtQuick.TreeView 2.15 as T

T.TreeView {
    id: treeView

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

    property Component icon

    property Component info: Rectangle {
        implicitWidth: text.width + 20
        implicitHeight: text.height
        color: bgColor(row2)
        Text {
            id: text
            x: 10
            text: display2
        }
    }

    property Component background: Rectangle {
        width: parent.width
        height: parent.height
        color: bgColor(row2)
    }

    property Item foreground

    delegate: DelegateChooser {
        DelegateChoice {
            column: 0 // the column where the tree is at

            Item {
                implicitWidth: indicatorLoader.x + indicatorLoader.width + labelLoader.width
                implicitHeight: Math.max(indicatorLoader.height, labelLoader.height)

                Loader {
                    id: backgroundLoader
                    property int row2: row
                    sourceComponent: background

                    Loader {
                        id: indicatorLoader
                        x: treeView.depth(row) * 20
                        width: item.width
                        height: item.height
                        property int row2: row
                        sourceComponent: indicator
                    }

                    Loader {
                        id: labelLoader
                        x: indicatorLoader.x + indicatorLoader.width
                        width: item.width
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
        }

        DelegateChoice {
            Loader {
                id: infoLoader
                width: item.width
                height: item.height
                property int row2: row
                property int column2: column
                property string display2: display
                sourceComponent: info
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
