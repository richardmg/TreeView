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
                implicitHeight: childrenRect.height
                color: bgColor(row)

                MouseArea {
                    anchors.fill: parent
                    onClicked: selectRow(row)
                }

                Item {
                    x: treeView.depth(row) * 20
                    width: childrenRect.width
                    height: childrenRect.height

                    Rectangle {
                        id: expandSign
                        visible: treeView.hasChildren(row)
                        y: 4
                        width: 11
                        height: 11
                        color: "transparent"
                        border.width: 1
                        border.color: Qt.rgba(0.7, 0.7, 0.7)
                        Rectangle {
                            anchors.centerIn: parent
                            color: "black"
                            width: 5
                            height: 1
                        }
                        Rectangle {
                            anchors.centerIn: parent
                            color: "black"
                            width: 1
                            height: 5
                            visible: !treeView.isExpanded(row)
                        }
                    }

                    Text {
                        id: text
                        anchors.left: expandSign.right
                        anchors.leftMargin: 2
                        anchors.verticalCenter: expandSign.verticalCenter
                        text: {
                            var text = "";
                            text += display
                        }
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            if (treeView.hasChildren(row))
                                treeView.toggleExpanded(row)
                            else
                                selectRow(row)
                        }
                    }
                }
            }
        }

        DelegateChoice {
            Rectangle {
                implicitWidth: text2.width
                implicitHeight: text2.height
                color: bgColor(row)
                Text {
                    id: text2
                    text: display
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: selectRow(row)
                }
            }
        }
    }

    property var selectedIndex

    function selectRow(row)
    {
        selectedIndex = treeView.modelIndex(row, 0)
    }

    function bgColor(row) {
        if (treeView.modelIndex(row, 0) === selectedIndex)
            return Qt.rgba(0.8, 0.8, 0.8, 1)
        else
            return Qt.rgba(0.9, 0.9, 0.9, 1)
    }
}
