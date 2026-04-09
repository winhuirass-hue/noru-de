import QtQuick
import Lomiri.DownloadDaemonListener 0.1

Window {
    visible: true
    width: 500
    height: 400
    title: "Download Tracker Demo"

    Column {
        anchors.centerIn: parent
        spacing: 10

        DownloadTracker {
            id: tracker

            service: "com.example.service"
            dbusPath: "/example/path"

            Component.onCompleted: {
                console.log("service:", tracker.service)
                console.log("dbusPath:", tracker.dbusPath)
                console.log("serviceReady:", tracker.serviceReady)
            }
        }
    }
}
