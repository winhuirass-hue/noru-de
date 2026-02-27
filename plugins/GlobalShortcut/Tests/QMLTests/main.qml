/**
 * @file main.qml
 * @brief GlobalShortcut Plugin QML Testing Example
 *
 * This QML file demonstrates how to use the GlobalShortcut plugin after porting from Qt5 to Qt6.
 *
 * Features demonstrated:
 * - shortcut: Read/write property using Qt enum (Qt.ControlModifier | Qt.AltModifier | Qt.Key_L)
 * - active: Read/write property (default: true)
 * - triggered(shortcut): Signal emitted when the registered shortcut key is pressed
 * - released(shortcut): Signal emitted when the registered shortcut key is released
 * - shortcutChanged: Signal emitted when shortcut property changes
 * - activeChanged: Signal emitted when active property changes
 *
 * Usage:
 * 1. Run the application
 * 2. Window auto-focuses when loaded (requestActivate)
 * 3. Press Ctrl+Alt+L to trigger the onTriggered signal
 * 4. Status text updates in real-time
 * 5. Console logs all signal emissions
 *
 * Qt Version: 6.8.2
 * Platform: Ubuntu 24.04.3 LTS
 */

import QtQuick
import QtQuick.Window
import GlobalShortcut 1.0

Window {
    width: 400
    height: 300
    visible: true
    title: "Global Shortcut Test"

    Component.onCompleted: {
        requestActivate()
    }

    GlobalShortcut {
        id: shortcutItem
        shortcut: Qt.ControlModifier | Qt.AltModifier | Qt.Key_L
        active: true

        onTriggered: function(shortcut) {
            statusText.text = "Triggered: " + shortcut
            console.log("Shortcut Triggered:", shortcut)
        }

        onReleased: function(shortcut) {
            statusText.text = "Released: " + shortcut
            console.log("Shortcut Released:", shortcut)
        }

        onShortcutChanged: function(shortcut) {
            console.log("Shortcut Changed:", shortcut)
        }

        onActiveChanged: function(active) {
            console.log("Active Changed:", active)
        }
    }

    Column {
        anchors.centerIn: parent
        spacing: 15

        Text {
            text: "Press Ctrl+Alt+L to trigger"
            font.bold: true
        }

        Text {
            text: "Shortcut: " + shortcutItem.shortcut
        }

        Text {
            text: "Active: " + shortcutItem.active
        }

        Text {
            id: statusText
            text: "Status: Waiting..."
            color: "blue"
            font.bold: true
        }
    }

}
