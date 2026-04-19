/*
 * Copyright (C) 2014-2016 Canonical Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

import QtQuick 2.15
import QtCore 5.15
import Lomiri.Components 1.3

Row {
    id: root
    spacing: overlayShown ? units.gu(2) : windowIsMaximized ? 0 : units.gu(1)
    Behavior on spacing {
        LomiriNumberAnimation {}
    }

    // to be set from outside
    property bool active: false
    property bool windowIsMaximized: false
    property bool closeButtonShown: true
    property bool maximizeButtonShown: true
    property bool minimizeButtonVisible: true
    property bool overlayShown

    readonly property color color: theme.palette.normal.baseText
    readonly property string wmThemeUserPath: "file://" + StandardPaths.writableLocation(StandardPaths.HomeLocation) + "/.config/noru/themes/wm/"
    readonly property string wmThemeSystemPath: "file:///usr/share/noru/wm/"

    signal closeClicked()
    signal minimizeClicked()
    signal maximizeClicked()
    signal maximizeVerticallyClicked()
    signal maximizeHorizontallyClicked()

    MouseArea {
        id: closeWindowButton
        objectName: "closeWindowButton"
        hoverEnabled: true
        height: parent.height
        width: height
        onClicked: root.closeClicked()
        visible: root.closeButtonShown

        Rectangle {
            anchors.fill: parent
            anchors.margins: windowIsMaximized ? units.dp(3) : 0
            radius: height / 2
            color: closeWindowButton.pressed ? "#B02828" : theme.palette.normal.negative
            visible: (parent.containsMouse || closeWindowButton.pressed) && !overlayShown
        }
        Icon {
            anchors.fill: parent
            anchors.margins: windowIsMaximized ? units.dp(6) : units.dp(3)
            source: "graphics/window-close.svg"
            color: root.active ? root.color : LomiriColors.jet
        }
    }

    MouseArea {
        id: minimizeWindowButton
        objectName: "minimizeWindowButton"
        hoverEnabled: true
        height: parent.height
        width: height
        onClicked: root.minimizeClicked()
        visible: root.minimizeButtonVisible

        ImageResolver {
            id: minimizeIconResolver
            candidates: [
                root.wmThemeUserPath + "minimize.svg",
                root.wmThemeSystemPath + "minimize.svg",
                "graphics/window-minimize.svg"
            ]
        }

        Rectangle {
            anchors.fill: parent
            anchors.margins: windowIsMaximized ? units.dp(3) : 0
            radius: height / 2
            color: minimizeWindowButton.pressed ? LomiriColors.slate : (root.active ? LomiriColors.graphite : LomiriColors.ash)
            visible: (parent.containsMouse || minimizeWindowButton.pressed) && !overlayShown
        }
        Icon {
            anchors.fill: parent
            anchors.margins: windowIsMaximized ? units.dp(6) : units.dp(3)
            source: "graphics/window-minimize.svg"
            color: root.active ? root.color : LomiriColors.slate
        }
    }

    MouseArea {
        id: maximizeWindowButton
        objectName: "maximizeWindowButton"
        hoverEnabled: true
        height: parent.height
        width: height
        visible: root.maximizeButtonShown
        acceptedButtons: Qt.LeftButton | Qt.RightButton | Qt.MiddleButton
        onClicked: {
            if (mouse.button == Qt.LeftButton) {
                root.maximizeClicked();
            } else if (mouse.button == Qt.RightButton) {
                root.maximizeHorizontallyClicked();
            } else if (mouse.button == Qt.MiddleButton) {
                root.maximizeVerticallyClicked();
            }
        }

        ImageResolver {
            id: maximizeIconResolver
            candidates: [
                root.wmThemeUserPath + "maximize.svg",
                root.wmThemeSystemPath + "maximize.svg",
                "graphics/window-maximize.svg"
            ]
        }

        ImageResolver {
            id: restoreIconResolver
            candidates: [
                root.wmThemeUserPath + "restore.svg",
                root.wmThemeSystemPath + "restore.svg",
                "graphics/window-window.svg"
            ]
        }

        Rectangle {
            anchors.fill: parent
            anchors.margins: windowIsMaximized ? units.dp(3) : 0
            radius: height / 2
            color: maximizeWindowButton.pressed ? LomiriColors.slate : (root.active ? LomiriColors.graphite : LomiriColors.ash)
            visible: (parent.containsMouse || maximizeWindowButton.pressed) && !overlayShown
        }
        Icon {
            anchors.fill: parent
            anchors.margins: windowIsMaximized ? units.dp(6) : units.dp(3)
            source: root.windowIsMaximized ? "graphics/window-window.svg" : "graphics/window-maximize.svg"
            color: root.active ? root.color : LomiriColors.slate
        }
    }
}
