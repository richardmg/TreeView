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

import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.1
import QtQuick.Layouts 1.14

import QtQuick.TreeView 2.15

Window {
    id: root
    width: 800
    height: 600
    visible: true
    visibility: Window.AutomaticVisibility

    RowLayout {
        id: controlRow

        CheckBox {
            id: configured
            text: "Configured"
        }

        Label {
            id: selectedLabel
            Layout.alignment: Qt.AlignVCenter
        }
    }

    Rectangle {
        anchors.top: controlRow.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 20
        border.width: 1

        TreeView {
            id: treeView
            anchors.fill:parent
            anchors.margins: 1
            model: fileSystemModel
            clip: true
            focus: true
            navigationMode: TreeView.List

            states: State {
                when: configured.checked
                PropertyChanges {
                    target: treeView
                    navigationMode: TreeView.Table
                    styleHints.indent: 15
                    styleHints.columnPadding: 20
                    styleHints.font.bold: true
                    styleHints.foregroundOdd: "#001a66"
                    styleHints.backgroundOdd: "#e6ecff"
                    styleHints.foregroundEven: "#001a66"
                    styleHints.backgroundEven: "#ccd9ff"
                    styleHints.foregroundCurrent: "#ebf0fa"
                    styleHints.backgroundCurrent: "#2e5cb8"
                    styleHints.indicator: "#000d33"
                    styleHints.overlay: navigationMode === TreeView.Table ? Qt.rgba(1, 1, 1) : "transparent"
                }
            }

            onCurrentModelIndexChanged: {
                var label = model.data(currentModelIndex, treeView.textRole)
                selectedLabel.text = "Selected row " + currentIndex.row + ", label: " + label
            }

            Keys.onReturnPressed: {
                // Set the second file inside the root folder as current:
                var rootIndex = fileSystemModel.index(0, 0)
                var childIndex = fileSystemModel.index(1, 0, rootIndex)
                currentIndex = mapFromModel(childIndex)
                if (!currentIndex.valid)
                    selectedLabel.text = childIndex + " is not visible"
            }
        }
    }
}
