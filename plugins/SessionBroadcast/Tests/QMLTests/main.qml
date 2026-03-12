import QtQuick
import QtQuick.Window
import SessionBroadcast 0.1

Window {
    width: 400
    height: 250
    visible: true
    title: "SessionBroadcast Test"

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
