import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Page {
    id: page

    background: Rectangle {
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#2b2b3c" }
            GradientStop { position: 1.0; color: "#1a1a28" }
        }
    }

    header: ToolBar {
        height: 56
        background: Rectangle {
            color: "#2b2b3c"
            Rectangle {
                anchors.bottom: parent.bottom
                width: parent.width; height: 1
                color: "#444455"
            }
        }
        RowLayout {
            anchors.fill: parent
            anchors.leftMargin: 16
            anchors.rightMargin: 16
            spacing: 12

            Label { text: "🔍"; font.pixelSize: 18; color: "#a0a0c0" }

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

            // Кнопка сортировки (без фильтра по тегам)
            Rectangle {
                width: 40; height: 40; radius: 10
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
                text: noteManager.searchQuery ? "Ничего не найдено" : "Нет заметок"
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
                visible: !noteManager.searchQuery
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
                onClicked: window.openEditor(modelData.id)
            }
        }
    }

    RoundButton {
        id: addButton
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 20
        width: 56; height: 56
        radius: 28
        text: "+"
        font.pixelSize: 24
        font.bold: true
        padding: 0
        contentItem: Text {
            text: addButton.text
            color: "#ffffff"
            font: addButton.font
            anchors.centerIn: parent
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
        background: Rectangle {
            radius: 28
            color: addButton.pressed ? "#6d28d9" : "#7c3aed"
            layer.enabled: true

        }
        onClicked: window.openEditor(-1)

        SequentialAnimation on scale {
            running: addButton.hovered
            loops: Animation.Infinite
            NumberAnimation { from: 1.0; to: 1.08; duration: 800; easing.type: Easing.InOutSine }
            NumberAnimation { from: 1.08; to: 1.0; duration: 800; easing.type: Easing.InOutSine }
        }
    }
}