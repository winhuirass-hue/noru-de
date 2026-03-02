import QtQuick
import QtQuick.Window
import UInput 0.1

Window {
    width: 400
    height: 500
    visible: true
    title: "UInput Plugin Test"

    Column {
        anchors.centerIn: parent
        spacing: 15

        Text {
            text: "Button Enum Values"
            font.bold: true
            font.pixelSize: 14
        }

        Text {
            text: "ButtonLeft: " + UInput.ButtonLeft
        }

        Text {
            text: "ButtonRight: " + UInput.ButtonRight
        }

        Text {
            text: "ButtonMiddle: " + UInput.ButtonMiddle
        }

        Text {
            text: ""
        }

        Text {
            text: "Q_INVOKABLE Methods Called:"
            font.bold: true
            font.pixelSize: 14
        }

        TextEdit {
            id: output
            width: 350
            height: 150
            readOnly: true
            font.family: "Courier"
            font.pixelSize: 10
            text: "Starting tests...\n"
            wrapMode: TextEdit.Wrap
        }
    }

    Timer {
        interval: 1000
        running: true
        repeat: false
        onTriggered: runTests()
    }

    function runTests() {
        output.text = ""

        output.text += "1. createMouse()\n"
        console.log("UInput Test: createMouse()")
        UInput.createMouse()

        output.text += "2. moveMouse(100, 50)\n"
        console.log("UInput Test: moveMouse(100, 50)")
        UInput.moveMouse(100, 50)

        output.text += "3. scrollMouse(0, 5)\n"
        console.log("UInput Test: scrollMouse(0, 5)")
        UInput.scrollMouse(0, 5)

        output.text += "4. scrollMouse(3, 0)\n"
        console.log("UInput Test: scrollMouse(3, 0)")
        UInput.scrollMouse(3, 0)

        output.text += "5. pressMouse(ButtonLeft)\n"
        console.log("UInput Test: pressMouse(ButtonLeft)")
        UInput.pressMouse(UInput.ButtonLeft)

        output.text += "6. releaseMouse(ButtonLeft)\n"
        console.log("UInput Test: releaseMouse(ButtonLeft)")
        UInput.releaseMouse(UInput.ButtonLeft)

        output.text += "7. pressMouse(ButtonRight)\n"
        console.log("UInput Test: pressMouse(ButtonRight)")
        UInput.pressMouse(UInput.ButtonRight)

        output.text += "8. releaseMouse(ButtonRight)\n"
        console.log("UInput Test: releaseMouse(ButtonRight)")
        UInput.releaseMouse(UInput.ButtonRight)

        output.text += "9. pressMouse(ButtonMiddle)\n"
        console.log("UInput Test: pressMouse(ButtonMiddle)")
        UInput.pressMouse(UInput.ButtonMiddle)

        output.text += "10. releaseMouse(ButtonMiddle)\n"
        console.log("UInput Test: releaseMouse(ButtonMiddle)")
        UInput.releaseMouse(UInput.ButtonMiddle)

        output.text += "11. removeMouse()\n"
        console.log("UInput Test: removeMouse()")
        UInput.removeMouse()

        output.text += "\n✓ All Tests Complete"
    }
}
