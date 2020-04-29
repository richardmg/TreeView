/****************************************************************************
**
** Copyright (C) 2020 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick 2.0
import Qt.labs.qmlmodels 1.0
import QtQuick.Shapes 1.0
import QtQuick.TreeView 2.15

TreeViewTemplate {
    id: control

    /*
        Note: if you need to tweak this style beyond the styleHints, either
        just assign a custom delegate directly to your TreeView, or copy this file
        into your project and use it as a starting point for your custom version.
    */
    styleHints.indent: 15
    styleHints.columnPadding: 20
    styleHints.foregroundOdd: "black"
    styleHints.backgroundOdd: "transparent"
    styleHints.foregroundEven: "black"
    styleHints.backgroundEven: "transparent"
    styleHints.foregroundCurrent: navigationMode === TreeView.List ? "white" : "black"
    styleHints.backgroundCurrent: navigationMode === TreeView.List ? "#005fe5" : "transparent"
    styleHints.overlay:  navigationMode === TreeView.Table ? Qt.rgba(0, 0, 0, 0.5) : "transparent"
    styleHints.indicator: "black"

    function bgColor(column, row) {
        if (currentIndex.row === row)
            return styleHints.backgroundCurrent
        else if (row % 2)
            return styleHints.backgroundOdd
        else
            return styleHints.backgroundEven
    }

    function fgColor(column, row) {
        if (currentIndex.row === row)
            return styleHints.foregroundCurrent
        else if (row % 2)
            return styleHints.foregroundOdd
        else
            return styleHints.foregroundEven
    }

    delegate: DelegateChooser {
        DelegateChoice {
            // The column where the tree is drawn
            column: 0

            Rectangle {
                id: treeNode
                implicitWidth: treeNodeLabel.x + treeNodeLabel.width + (styleHints.columnPadding / 2)
                implicitHeight: Math.max(indicator.height, treeNodeLabel.height)
                color: bgColor(column, row)

                property bool hasChildren: TreeView.hasChildren
                property bool isExpanded: TreeView.isExpanded
                property int depth: TreeView.depth

                Text {
                    id: indicator
                    x: depth * styleHints.indent
                    width: 15
                    color: styleHints.indicator
                    font: styleHints.font
                    text: hasChildren ? (isExpanded ? "▼" : "▶") : ""
                    anchors.verticalCenter: parent.verticalCenter
                }

                Text {
                    id: treeNodeLabel
                    x: indicator.x + Math.max(styleHints.indent, indicator.width * 1.5)
                    clip: true
                    color: fgColor(column, row)
                    font: styleHints.font
                    text: model.display
                }

                MouseArea {
                    x: indicator.x
                    width: indicator.width
                    height: indicator.height
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
                implicitWidth: infoLabel.x + infoLabel.width + (styleHints.columnPadding / 2)
                color: bgColor(column, row)
                Text {
                    id: infoLabel
                    x: styleHints.columnPadding / 2
                    color: fgColor(column, row)
                    font: styleHints.font
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
            strokeColor: styleHints.overlay
            strokeWidth: 1
            strokeStyle: ShapePath.DashLine
            dashPattern: [1, 2]
            startX: currentItem ? currentItem.x + strokeWidth : 0
            startY: currentItem ? currentItem.y + strokeWidth : 0
            property real endX: currentItem ? currentItem.width + startX - (strokeWidth * 2) : 0
            property real endY: currentItem ? currentItem.height + startY - (strokeWidth * 2) : 0
            PathLine { x: path.endX; y: path.startY }
            PathLine { x: path.endX; y: path.endY }
            PathLine { x: path.startX; y: path.endY }
            PathLine { x: path.startX; y: path.startY }
        }
    }

}
