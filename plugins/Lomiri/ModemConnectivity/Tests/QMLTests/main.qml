import QtQuick
import Lomiri.ModemConnectivity

Window {
    width: 640
    height: 480
    visible: true
    title: "ModemConnectivity Test"

    Component.onCompleted: {
        if (ModemConnectivity) {
            console.log("Singleton loaded")
        }

        ModemConnectivity.unlockAllModems()
    }
}
