import QtQuick
import QtQuick.Window
import BatteryMonitor 1.0

Window {
    width: 400
    height: 250
    visible: true
    title: "Battery Monitor Test"

    Column {
        anchors.centerIn: parent
        spacing: 15

        Text {
            text: "Charging: " + BatteryMonitor.charging
        }

        Text {
            text: "Fully Charged: " + BatteryMonitor.fullyCharged
        }

        Text {
            text: BatteryMonitor.timeToFull > 0
                  ? "Time To Full: " + BatteryMonitor.timeToFull
                  : "Time To Full: Not Available"
        }

        Text {
            text: "State: " + BatteryMonitor.state()
        }
    }

    Timer {
        interval: 3000
        running: true
        repeat: true

        onTriggered: {
            console.log("Charging:", BatteryMonitor.charging)
            console.log("Fully Charged:", BatteryMonitor.fullyCharged)
            console.log("TimeToFull:" + BatteryMonitor.timeToFull)
            console.log("State:", BatteryMonitor.state())
        }
    }
}
