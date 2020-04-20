import QtQuick 2.0
import Qt.labs.qmlmodels 1.0
import QtQuick.TreeView 2.15 as T

T.TreeView {
    id: treeView

    delegate: DelegateChooser {
        DelegateChoice {
            column: 0 // the column where the tree is at

            Rectangle {
                implicitWidth: childrenRect.width
                implicitHeight: 20
                color: bgColor(row)

                MouseArea {
                    anchors.fill: parent
                    onClicked: treeView.currentRow = row
                }

                Item {
                    id: label
                    x: treeView.depth(row) * 20
                    width: childrenRect.width
                    height: parent.height

                    Rectangle {
                        id: expandSign
                        visible: treeView.hasChildren(row)
                        y: 4
                        width: 13
                        height: 13
                        color: "transparent"
                        border.width: 1
                        border.color: Qt.rgba(0.7, 0.7, 0.7)

                        Text {
                            x: 2.5
                            y: 1
                            text: treeView.isExpanded(row) ? "─" : "┼"
                            font.pixelSize: 8
                        }
                    }

                    Rectangle {
                        id: fileSign
                        visible: !expandSign.visible
                        x: expandSign.width / 2
                        width: 1
                        height: parent.height
                        color: expandSign.border.color
                        Rectangle {
                            width: 6
                            height: 1
                            y: parent.height / 2
                            color: fileSign.color
                        }
                    }

                    Rectangle {
                        id: lineToSiblingAbove
                        color: expandSign.border.color
                        x: expandSign.width / 2
                        width: 1
                        height: 4
                        visible: row != 0 && treeView.depth(row) === treeView.depth(row - 1)
                    }

                    Rectangle {
                        id: lineToSiblingBelow
                        color: expandSign.border.color
                        x: expandSign.width / 2
                        anchors.top: expandSign.bottom
                        width: 1
                        height: 4
                        visible: row != 0 && treeView.depth(row) === treeView.depth(row + 1)
                    }

                    Text {
                        id: text
                        anchors.left: expandSign.right
                        anchors.leftMargin: 4
                        anchors.verticalCenter: expandSign.verticalCenter
                        text: display
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
                    onClicked: treeView.currentRow = row
                }
            }
        }
    }

    property var selectedIndex

    function bgColor(row) {
        if (treeView.modelIndex(row, 0) === selectedIndex)
            return Qt.rgba(0.8, 0.8, 0.8, 1)
        else
            return Qt.rgba(0.9, 0.9, 0.9, 1)
    }
}
