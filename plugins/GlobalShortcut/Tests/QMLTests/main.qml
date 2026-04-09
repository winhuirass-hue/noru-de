import QtQuick
import QtQuick.Window
import GlobalShortcut 1.0

Window {
    width: 400
    height: 300
    visible: true
    title: "GlobalShortcut Test"

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
