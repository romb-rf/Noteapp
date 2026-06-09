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
    property string noteReminderDate: ""   // ДД.ММ.ГГГГ
    property string noteReminderTime: ""   // ЧЧ:ММ

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
                if (noteObj.reminder) {
                    var remDate = new Date(noteObj.reminder)
                    noteReminderDate = Qt.formatDate(remDate, "dd.MM.yyyy")
                    noteReminderTime = Qt.formatTime(remDate, "hh:mm")
                } else {
                    noteReminderDate = ""
                    noteReminderTime = ""
                }
                noteCreated = noteObj.created
                    ? new Date(noteObj.created).toLocaleString(Qt.locale(), "yyyy-MM-dd hh:mm")
                    : ""
            }
        } else {
            noteTitle = ""; noteContent = ""; noteColor = "#ffffff"; notePinned = false
            noteTags = ""; noteReminderDate = ""; noteReminderTime = ""; noteCreated = ""
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
                        text: noteReminderDate
                        placeholderText: "ДД.ММ.ГГГГ"
                        color: "#ffffff"
                        inputMethodHints: Qt.ImhDate
                        background: Rectangle { radius: 12; color: "#323248"; border.color: "#4a4a6a" }
                        onTextChanged: noteReminderDate = text
                    }
                    TextField {
                        id: reminderTimeField
                        Layout.fillWidth: true
                        text: noteReminderTime
                        placeholderText: "ЧЧ:ММ"
                        color: "#ffffff"
                        inputMethodHints: Qt.ImhTime
                        background: Rectangle { radius: 12; color: "#323248"; border.color: "#4a4a6a" }
                        onTextChanged: noteReminderTime = text
                    }
                    Rectangle {
                        width: 40; height: 40; radius: 10
                        color: clearReminderMouse.pressed ? "#4a4a6a" : "#363649"
                        Text { anchors.centerIn: parent; text: "✕"; color: "#c0c0ff" }
                        MouseArea {
                            id: clearReminderMouse
                            anchors.fill: parent
                            onClicked: {
                                noteReminderDate = ""
                                noteReminderTime = ""
                            }
                        }
                    }
                }
            }

            // Яркие цвета
            ColumnLayout {
                spacing: 10
                Label {
                    text: "ЦВЕТ"
                    font.pixelSize: 11; font.bold: true; font.letterSpacing: 1.5; color: "#8b5cf6"
                }
                RowLayout {
                    spacing: 14
                    property var colorList: [
                        "#ffffff",  // белый
                        "#ff6b6b",  // красный
                        "#51cf66",  // зелёный
                        "#339af0",  // синий
                        "#ffd43b",  // жёлтый
                        "#ff6eb4",  // розовый
                        "#ff922b"   // оранжевый
                    ]
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

                    // Подготовка напоминания: если поля не пусты – парсим, иначе – невалидный NaN
                    var reminder = new Date(NaN)   // теперь по умолчанию невалидный
                    var dateStr = reminderDateField.text.trim()
                    var timeStr = reminderTimeField.text.trim()
                    if (dateStr !== "" && timeStr !== "") {
                        var parts = dateStr.split(".")
                        if (parts.length === 3) {
                            var day = parseInt(parts[0], 10)
                            var month = parseInt(parts[1], 10) - 1
                            var year = parseInt(parts[2], 10)
                            var timeParts = timeStr.split(":")
                            var hours = parseInt(timeParts[0], 10)
                            var minutes = parseInt(timeParts[1], 10)
                            if (!isNaN(year) && !isNaN(month) && !isNaN(day) &&
                                !isNaN(hours) && !isNaN(minutes)) {
                                reminder = new Date(year, month, day, hours, minutes)
                            }
                        }
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