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
