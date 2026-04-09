import QtQuick
import QtQuick.Window
import Lomiri.ApplicationMenu 0.1

Window {
    width: 400
    height: 300
    visible: true
    title: "ApplicationMenu Test"

    // MenuServicePath - QML_UNCREATABLE (cannot create instance)
    MenuServicePath{

    }

    // DBusApplicationMenuRegistry - QML_SINGLETON with PROTECTED constructor (cannot access)
    Component.onCompleted: {
        console.log(DBusApplicationMenuRegistry)
    }
}
