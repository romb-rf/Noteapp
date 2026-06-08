import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Page {
    id: page

    StackView.onActivated: {
        listView.model = null
        listView.model = noteManager.filteredNotes
    }

    background: Rectangle {
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#2b2b3c" }
            GradientStop { position: 1.0; color: "#1a1a28" }
        }
    }

    header: ToolBar {
        background: Rectangle {
            color: "#2b2b3c"
            opacity: 0.95
            Rectangle {
                anchors.bottom: parent.bottom
                width: parent.width; height: 1
                color: "#444455"
            }
        }
        RowLayout {
            anchors.fill: parent
            anchors.leftMargin: 16; anchors.rightMargin: 16
            spacing: 12

            Label {
                text: "🔍"
                font.pixelSize: 18
                color: "#a0a0c0"
            }

            TextField {
                id: searchField
                Layout.fillWidth: true
                placeholderText: "Поиск заметок..."
                placeholderTextColor: "#6b6b80"
                color: "#ffffff"
                background: Rectangle {
                    radius: 12
                    color: "#363649"
                    border.color: "#4a4a6a"
                }
                onTextChanged: noteManager.searchQuery = text
            }

            Rectangle {
                width: 40; height: 40
                radius: 10
                color: sortMouseArea.pressed ? "#4a4a6a" : "#363649"
                Text {
                    anchors.centerIn: parent
                    text: noteManager.sortNewestFirst ? "↓" : "↑"
                    color: "#c0c0ff"
                    font.pixelSize: 20
                }
                MouseArea {
                    id: sortMouseArea
                    anchors.fill: parent
                    onClicked: noteManager.sortNewestFirst = !noteManager.sortNewestFirst
                }
            }
        }
    }

    Item {
        anchors.fill: parent
        anchors.topMargin: 10

        Column {
            anchors.centerIn: parent
            spacing: 16
            visible: noteManager.filteredNotes.length === 0

            Label {
                anchors.horizontalCenter: parent.horizontalCenter
                text: "📝"
                font.pixelSize: 64
                opacity: 0.7
            }
            Label {
                text: "Нет заметок"
                font.pixelSize: 20
                font.bold: true
                color: "#b0b0d0"
                anchors.horizontalCenter: parent.horizontalCenter
            }
            Label {
                text: "Нажмите +, чтобы создать первую"
                font.pixelSize: 14
                color: "#7a7a99"
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }

        ListView {
            id: listView
            anchors.fill: parent
            anchors.margins: 12
            clip: true
            spacing: 10
            model: noteManager.filteredNotes
            visible: noteManager.filteredNotes.length > 0

            delegate: NoteDelegate {
                width: listView.width
                onClicked: {
                    stackView.push(noteEditPage, { noteId: modelData.id })
                }
            }
        }
    }

    RoundButton {
        id: addButton
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 24
        width: 60; height: 60
        text: "+"
        font.pixelSize: 28
        palette.button: "#7c3aed"
        palette.buttonText: "#ffffff"

        background: Rectangle {
            radius: 30
            color: addButton.pressed ? "#6d28d9" : "#7c3aed"
            layer.enabled: true

        }

        onClicked: stackView.push(noteEditPage, { noteId: -1 })

        SequentialAnimation on scale {
            running: addButton.hovered
            loops: Animation.Infinite
            NumberAnimation { from: 1.0; to: 1.05; duration: 800; easing.type: Easing.InOutSine }
            NumberAnimation { from: 1.05; to: 1.0; duration: 800; easing.type: Easing.InOutSine }
        }
    }
}