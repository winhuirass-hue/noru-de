import QtQuick
import Lomiri.InputInfo 0.1

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    QDeclarativeInputDeviceModel
    {
        id:qDeclarativeInputDeviceModel
        Component.onCompleted: {
            console.log(deviceFilter)
            console.log(count)

            console.log(indexOf("/dev/input/event0"))
        }
    }

    LomiriInputDevice{

    }

}
