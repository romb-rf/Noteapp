import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    id: window
    visible: true
    width: 420
    height: 720
    title: "Заметки"
    color: "#1e1e2e"

    property int currentNoteId: -1
    property bool editorVisible: false

    // Вызывается из C++ для показа тоста
    function showToast(title, body) {
        toastText.text = title + ": " + body
        toast.visible = true
        toastShow.restart()
    }

    // Закрытие – сворачиваем в трей (явно указываем параметр close)
    onClosing: function(close) {
        trayHelper.hideWindow()
        close.accepted = false
    }

    NotesListPage {
        id: notesListPage
        anchors.fill: parent
        visible: !editorVisible
    }

    Loader {
        id: editorLoader
        anchors.fill: parent
        active: true
        visible: editorVisible

        sourceComponent: NoteEditPage {
            noteId: window.currentNoteId

            onSaveClicked: window.editorVisible = false
            onBackClicked: window.editorVisible = false
        }
    }

    function openEditor(noteId) {
        window.currentNoteId = noteId
        window.editorVisible = true
    }

    // Тост
    Rectangle {
        id: toast
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 20
        width: parent.width - 40
        height: 60
        radius: 14
        color: "#7c3aed"
        opacity: 0
        visible: false
        z: 100

        RowLayout {
            anchors.fill: parent
            anchors.margins: 12
            Text {
                Layout.fillWidth: true
                text: toastText.text
                color: "#ffffff"
                font.pixelSize: 14
                wrapMode: Text.WordWrap
            }
            Rectangle {
                width: 32; height: 32; radius: 16
                color: "#ffffff20"
                Text {
                    anchors.centerIn: parent
                    text: "✕"
                    color: "#ffffff"
                    font.pixelSize: 16
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: toastHide.start()
                }
            }
        }

        Text {
            id: toastText
            visible: false
            property string text: ""
        }

        SequentialAnimation {
            id: toastShow
            NumberAnimation { target: toast; property: "opacity"; to: 1; duration: 300 }
            PauseAnimation { duration: 4000 }
            ScriptAction { script: toastHide.start() }
        }

        SequentialAnimation {
            id: toastHide
            NumberAnimation { target: toast; property: "opacity"; to: 0; duration: 300 }
            ScriptAction { script: toast.visible = false }
        }
    }
}