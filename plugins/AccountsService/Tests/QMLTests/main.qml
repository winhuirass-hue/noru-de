import QtQuick
import QtQuick.Window
import AccountsService 0.1

Window {
    width: 600
    height: 600
    visible: true
    title: "AccountsService Test"

    Column {
        anchors.centerIn: parent
        spacing: 10

        Text {
            text: "user: " + AccountsService.user
        }

        Text {
            text: "realName: " + AccountsService.realName
        }

        Text {
            text: "email: " + AccountsService.email
        }

        Text {
            text: "backgroundFile: " + AccountsService.backgroundFile
        }

        Text {
            text: "demoEdges: " + AccountsService.demoEdges
        }

        Text {
            text: "enableFingerprintIdentification: " + AccountsService.enableFingerprintIdentification
        }

        Text {
            text: "enableLauncherWhileLocked: " + AccountsService.enableLauncherWhileLocked
        }

        Text {
            text: "enableIndicatorsWhileLocked: " + AccountsService.enableIndicatorsWhileLocked
        }

        Text {
            text: "hideNotificationContentWhileLocked: " + AccountsService.hideNotificationContentWhileLocked
        }

        Text {
            text: "statsWelcomeScreen: " + AccountsService.statsWelcomeScreen
        }

        Text {
            text: "passwordDisplayHint: " + AccountsService.passwordDisplayHint
        }

        Text {
            text: "pincodeLength: " + AccountsService.pincodeLength
        }

        Text {
            text: "failedLogins: " + AccountsService.failedLogins
        }

        Text {
            text: "failedFingerprintLogins: " + AccountsService.failedFingerprintLogins
        }

        Text {
            text: "pinCodePromptManager: " + AccountsService.pinCodePromptManager
        }

        Text {
            text: "defaultPinCodePromptManager: " + AccountsService.defaultPinCodePromptManager
        }

        Text {
            text: "demoEdgesCompleted: " + AccountsService.demoEdgesCompleted
        }

        Text {
            text: "keymaps: " + AccountsService.keymaps
        }

        Text {
            text: "markDemoEdgeCompleted('top'): " + AccountsService.markDemoEdgeCompleted("top")
        }
    }
}
