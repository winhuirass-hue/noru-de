/**
 * @file main.qml
 * @brief SessionBroadcast Plugin QML Testing Example
 *
 * This QML file demonstrates how to test and access all Q_INVOKABLE
 * functions exposed by the SessionBroadcast plugin after porting from Qt5 to Qt6.
 *
 * Features tested:
 * - requestUrlStart(username, url): Invokable method to broadcast a URL start request via DBus
 * - requestHomeShown(username): Invokable method to broadcast a show-home request via DBus
 *
 * Note: This plugin has no Q_PROPERTY declarations.
 *
 * Qt Version: 6.8.2 (required)
 * Platform: Ubuntu 24.04.3 LTS
 */

import QtQuick
import QtQuick.Window
import SessionBroadcast 0.1

Window {
    width: 400
    height: 250
    visible: true
    title: "Session Broadcast Test"

    Column {
        anchors.centerIn: parent
        spacing: 15

        Text {
            text: "=== Q_INVOKABLE Functions ==="
            font.bold: true
        }

        Text {
            text: "requestUrlStart: " + SessionBroadcast.requestUrlStart("testuser", "https://example.com")
        }

        Text {
            text: "requestHomeShown: " + SessionBroadcast.requestHomeShown("testuser")
        }
    }

    Timer {
        interval: 3000
        running: true
        repeat: true

        onTriggered: {
            console.log("requestUrlStart:", SessionBroadcast.requestUrlStart("testuser", "https://example.com"))
            console.log("requestHomeShown:", SessionBroadcast.requestHomeShown("testuser"))
        }
    }
}
