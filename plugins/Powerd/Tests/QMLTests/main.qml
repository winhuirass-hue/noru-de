/**
 * @file main.qml
 * @brief Powerd Plugin QML Testing Example
 *
 * Tests Q_PROPERTY and Q_INVOKABLE functions of Powerd plugin (Qt6).
 *
 * Features tested:
 * - status: Read-only property (0: Off, 1: On)
 * - setStatus(): Invokable method
 *
 * Qt Version: 6.8.2 | Platform: Ubuntu 24.04.3 LTS
 */

import QtQuick
import QtQuick.Window
import QtQuick.Controls
import Powerd 0.1

Window {
    width: 400
    height: 300
    visible: true
    title: "Powerd Plugin Test"

    Column {
        anchors.centerIn: parent
        spacing: 15

        Text {
            text: "Q_PROPERTY: status"
            font.bold: true
        }

        Text {
            text: "Display Status: " + (Powerd.status === Powerd.On ? "ON" : "OFF")
        }

        Text {
            text: "Status Value: " + Powerd.status
        }

        Text {
            text: "Status Enum - Off: " + Powerd.Off + ", On: " + Powerd.On
        }

        Rectangle {
            width: 200
            height: 1
            color: "#cccccc"
        }

        Text {
            text: "Q_INVOKABLE: setStatus()"
            font.bold: true
        }

        Button {
            text: "setStatus(On, PowerKey)"
            onClicked: {
                console.log("Test: setStatus(Powerd.On, Powerd.PowerKey)")
                Powerd.setStatus(Powerd.On, Powerd.PowerKey)
            }
        }

        Button {
            text: "setStatus(Off, Inactivity)"
            onClicked: {
                console.log("Test: setStatus(Powerd.Off, Powerd.Inactivity)")
                Powerd.setStatus(Powerd.Off, Powerd.Inactivity)
            }
        }

        Button {
            text: "setStatus(toggle, Notification)"
            onClicked: {
                var newStatus = Powerd.status === Powerd.On ? Powerd.Off : Powerd.On
                console.log("Test: setStatus(toggle, Powerd.Notification)")
                Powerd.setStatus(newStatus, Powerd.Notification)
            }
        }
    }

    Timer {
        interval: 3000
        running: true
        repeat: true

        onTriggered: {
            console.log("Status:", (Powerd.status === Powerd.On ? "ON" : "OFF"), 
                       "| Value:", Powerd.status)
        }
    }
}
