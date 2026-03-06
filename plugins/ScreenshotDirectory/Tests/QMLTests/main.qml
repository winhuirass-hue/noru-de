import QtQuick
import QtQuick.Window
import ScreenshotDirectory 0.1

Window {
    width: 600
    height: 200
    visible: true
    title: "ScreenshotDirectory Test"

    ScreenshotDirectory {
        id: screenshotDirectory
    }

    Column {
        anchors.centerIn: parent
        spacing: 15

        Text {
            text: "ScreenshotDirectory - makeFileName():"
            font.bold: true
        }

        Text {
            text: screenshotDirectory.makeFileName()
            font.pixelSize: 12
            wrapMode: Text.Wrap
            width: 550
        }
    }
}
