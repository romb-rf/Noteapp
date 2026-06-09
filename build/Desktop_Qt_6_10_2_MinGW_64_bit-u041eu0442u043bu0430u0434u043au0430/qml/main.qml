import QtQuick
import QtQuick.Controls

ApplicationWindow {
    id: window
    visible: true
    width: 420
    height: 720
    title: "Заметки"
    color: "#1e1e2e"

    property int currentNoteId: -1
    property bool editorVisible: false

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
}