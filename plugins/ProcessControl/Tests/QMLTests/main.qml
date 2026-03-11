import QtQuick
import ProcessControl 0.1

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("ProcessControl Plugin Test")

    Component.onCompleted: {
        console.log(ProcessControl.awakenProcesses)
    }
}


