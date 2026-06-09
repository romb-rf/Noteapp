import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Page {
    id: editPage
    property int noteId: -1
    property string noteTitle: ""
    property string noteContent: ""
    property color noteColor: "#ffffff"
    property bool notePinned: false
    property string noteCreated: ""
    property string noteTags: ""
    property date noteReminder: new Date(0)

    signal saveClicked()
    signal backClicked()

    function loadNote(id) {
        if (id >= 0) {
            var noteObj = noteManager.noteById(id)
            if (noteObj) {
                noteTitle = noteObj.title || ""
                noteContent = noteObj.content || ""
                noteColor = noteObj.color || "#ffffff"
                notePinned = noteObj.pinned || false
                noteTags = noteObj.tags ? noteObj.tags.join(", ") : ""
                noteReminder = noteObj.reminder ? new Date(noteObj.reminder) : new Date(0)
                noteCreated = noteObj.created
                    ? new Date(noteObj.created).toLocaleString(Qt.locale(), "yyyy-MM-dd hh:mm")
                    : ""
            }
        } else {
            noteTitle = ""; noteContent = ""; noteColor = "#ffffff"; notePinned = false
            noteTags = ""; noteReminder = new Date(0); noteCreated = ""
        }
    }

    onNoteIdChanged: loadNote(noteId)
    Component.onCompleted: loadNote(noteId)

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

            Rectangle {
                width: 40; height: 40; radius: 10
                color: backMouseArea.pressed ? "#4a4a6a" : "transparent"
                Text { anchors.centerIn: parent; text: "←"; color: "#c0c0ff"; font.pixelSize: 22 }
                MouseArea {
                    id: backMouseArea
                    anchors.fill: parent
                    onClicked: backClicked()
                }
            }

            Label {
                text: noteId >= 0 ? "Редактирование" : "Новая заметка"
                font.bold: true; font.pixelSize: 18; color: "#ffffff"
                Layout.fillWidth: true
            }

            Rectangle {
                width: 40; height: 40; radius: 10
                visible: noteId >= 0
                color: deleteMouseArea.pressed ? "#4a4a6a" : "transparent"
                Text { anchors.centerIn: parent; text: "🗑"; font.pixelSize: 20 }
                MouseArea {
                    id: deleteMouseArea
                    anchors.fill: parent
                    onClicked: { noteManager.removeNote(noteId); backClicked() }
                }
            }
        }
    }

    Flickable {
        anchors.fill: parent
        contentWidth: width
        contentHeight: layout.implicitHeight + 40
        boundsBehavior: Flickable.StopAtBounds
        clip: true

        ColumnLayout {
            id: layout
            width: parent.width - 40
            x: 20; y: 20
            spacing: 20

            // Заголовок
            ColumnLayout {
                spacing: 8
                Label {
                    text: "ЗАГОЛОВОК"
                    font.pixelSize: 11; font.bold: true; font.letterSpacing: 1.5; color: "#8b5cf6"
                }
                TextArea {
                    id: titleField
                    Layout.fillWidth: true; Layout.minimumHeight: 50
                    text: noteTitle
                    color: "#ffffff"; font.pixelSize: 20; font.bold: true
                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                    placeholderText: "Введите заголовок"; placeholderTextColor: "#6b6b80"
                    selectionColor: "#7c3aed"; selectByMouse: true
                    background: Rectangle { radius: 14; color: "#323248"; border.color: "#4a4a6a" }
                }
            }

            // Текст
            ColumnLayout {
                spacing: 8
                Label {
                    text: "ТЕКСТ ЗАМЕТКИ"
                    font.pixelSize: 11; font.bold: true; font.letterSpacing: 1.5; color: "#8b5cf6"
                }
                TextArea {
                    id: contentArea
                    Layout.fillWidth: true; Layout.minimumHeight: 200
                    text: noteContent
                    color: "#e0e0ff"; font.pixelSize: 15
                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                    placeholderText: "Начните писать..."; placeholderTextColor: "#6b6b80"
                    selectionColor: "#7c3aed"; selectByMouse: true
                    background: Rectangle { radius: 14; color: "#323248"; border.color: "#4a4a6a" }
                }
            }

            // Теги
            ColumnLayout {
                spacing: 8
                Label {
                    text: "ТЕГИ (через запятую)"
                    font.pixelSize: 11; font.bold: true; font.letterSpacing: 1.5; color: "#8b5cf6"
                }
                TextField {
                    id: tagsField
                    Layout.fillWidth: true
                    text: noteTags
                    color: "#ffffff"
                    placeholderText: "например: работа, важно, идеи"
                    placeholderTextColor: "#6b6b80"
                    background: Rectangle { radius: 12; color: "#323248"; border.color: "#4a4a6a" }
                }
            }

            // Напоминание
            ColumnLayout {
                spacing: 8
                Label {
                    text: "НАПОМИНАНИЕ"
                    font.pixelSize: 11; font.bold: true; font.letterSpacing: 1.5; color: "#8b5cf6"
                }
                RowLayout {
                    spacing: 8
                    TextField {
                        id: reminderDateField
                        Layout.fillWidth: true
                        text: noteReminder.getTime() ? Qt.formatDate(noteReminder, "yyyy-MM-dd") : ""
                        placeholderText: "ГГГГ-ММ-ДД"
                        color: "#ffffff"
                        background: Rectangle { radius: 12; color: "#323248"; border.color: "#4a4a6a" }
                    }
                    TextField {
                        id: reminderTimeField
                        Layout.fillWidth: true
                        text: noteReminder.getTime() ? Qt.formatTime(noteReminder, "hh:mm") : ""
                        placeholderText: "ЧЧ:ММ"
                        color: "#ffffff"
                        background: Rectangle { radius: 12; color: "#323248"; border.color: "#4a4a6a" }
                    }
                    Rectangle {
                        width: 40; height: 40; radius: 10
                        color: clearReminderMouse.pressed ? "#4a4a6a" : "#363649"
                        Text { anchors.centerIn: parent; text: "✕"; color: "#c0c0ff" }
                        MouseArea {
                            id: clearReminderMouse
                            anchors.fill: parent
                            onClicked: {
                                noteReminder = new Date(0)
                                reminderDateField.text = ""
                                reminderTimeField.text = ""
                            }
                        }
                    }
                }
            }

            // Цвет
            ColumnLayout {
                spacing: 10
                Label {
                    text: "ЦВЕТ"
                    font.pixelSize: 11; font.bold: true; font.letterSpacing: 1.5; color: "#8b5cf6"
                }
                RowLayout {
                    spacing: 14
                    property var colorList: ["#ffffff","#ffb3b3","#b3ffb3","#b3b3ff","#ffffb3","#ffb3ff"]
                    Repeater {
                        model: parent.colorList
                        Rectangle {
                            width: 36; height: 36; radius: 18
                            color: modelData
                            border.width: noteColor == modelData ? 3 : 1
                            border.color: noteColor == modelData ? "#7c3aed" : "#555570"
                            MouseArea {
                                anchors.fill: parent
                                onClicked: noteColor = modelData
                            }
                            Label {
                                anchors.centerIn: parent
                                text: "✓"
                                color: modelData === "#ffffff" ? "#333" : "#fff"
                                visible: noteColor == modelData
                                font.bold: true
                            }
                        }
                    }
                }
            }

            Label {
                visible: noteId >= 0 && noteCreated !== ""
                text: "📅 Создана: " + noteCreated
                color: "#8888aa"
                font.pixelSize: 13
            }

            Button {
                Layout.alignment: Qt.AlignHCenter
                Layout.topMargin: 10
                implicitWidth: 200; implicitHeight: 48
                text: "Сохранить"
                font.pixelSize: 16; font.bold: true
                palette.button: "#7c3aed"
                palette.buttonText: "#ffffff"
                background: Rectangle {
                    radius: 14
                    color: parent.pressed ? "#6d28d9" : "#7c3aed"
                    layer.enabled: true

                }
                onClicked: {
                    if (titleField.text.trim() === "" && contentArea.text.trim() === "") {
                        backClicked()
                        return
                    }
                    var tagsArray = tagsField.text.split(",").map(t => t.trim()).filter(t => t !== "")
                    var reminder = new Date(0)
                    if (reminderDateField.text && reminderTimeField.text) {
                        var dt = reminderDateField.text + "T" + reminderTimeField.text + ":00"
                        reminder = new Date(dt)
                    }
                    noteManager.addOrUpdateNoteFields(
                        noteId, titleField.text, contentArea.text, noteColor, notePinned,
                        tagsArray, reminder
                    )
                    saveClicked()
                }
            }
        }
    }
}