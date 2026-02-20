/**
 * @file main.qml
 * @brief BatteryMonitor Plugin QML Testing Example
 *
 * This QML file demonstrates how to test and access all Q_PROPERTY and Q_INVOKABLE
 * functions exposed by the BatteryMonitor plugin after porting from Qt5 to Qt6.
 *
 * Features tested:
 * - charging: Read-only property indicating if device is charging
 * - fullyCharged: Read-only property indicating 100% battery charge
 * - timeToFull: Read-only property with seconds to full charge (-1: no battery, -2: unavailable)
 * - state(): Invokable method returning battery state (0: UNKNOWN, 1: CHARGING, 2: DISCHARGING, 3: EMPTY, 4: FULLY_CHARGED)
 *
 * The Timer validates real-time signal emissions every 3 seconds.
 * DBus retrieves battery information from the system UPower daemon.
 *
 * Qt Version: 6.8.2 (required)
 * Platform: Ubuntu 24.04.3 LTS
 */

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
