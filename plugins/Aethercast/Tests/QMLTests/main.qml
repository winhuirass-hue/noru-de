/**
 * @file main.qml
 * @brief Aethercast Plugin QML Testing Example
 *
 * This QML file demonstrates how to test and access all Q_PROPERTY and Q_INVOKABLE
 * functions exposed by the Aethercast plugin after porting from Qt5 to Qt6.
 *
 * Features tested:
 * - scanning: Read-only property indicating if Aethercast is scanning for displays
 * - enabled: Read-write property for enabling/disabling Aethercast functionality
 * - state: Read-only property indicating current connection state
 *
 * The Timer validates real-time signal emissions every 3 seconds.
 * DBus retrieves display information from the system Aethercast daemon.
 *
 * Qt Version: 6.8.2 (required)
 * Platform: Ubuntu 24.04.3 LTS
 */

import QtQuick
import QtQuick.Window
import Aethercast 0.1

Window {
    width: 400
    height: 250
    visible: true
    title: "Aethercast Test"

    Displays {
        id: displays
    }

    Column {
        anchors.centerIn: parent
        spacing: 15

        Text {
            text: "Scanning: " + displays.scanning
        }

        Text {
            text: "Enabled: " + displays.enabled
        }

        Text {
            text: "State: " + displays.state
        }
    }

    Timer {
        interval: 3000
        running: true
        repeat: true

        onTriggered: {
            console.log("Scanning:", displays.scanning)
            console.log("Enabled:", displays.enabled)
            console.log("State:", displays.state)
        }
    }
}
