import QtQuick
import QtQuick.Controls

ApplicationWindow {
    id: window
    visible: true
    width: 420
    height: 720
    title: "Заметки"
    color: "#1e1e2e"

    // Идентификатор текущей редактируемой заметки
    property int currentNoteId: -1
    // Флаг видимости редактора
    property bool editorVisible: false

    // Главная страница со списком (видна, когда редактор скрыт)
    NotesListPage {
        id: notesListPage
        anchors.fill: parent
        visible: !editorVisible
    }

    // Редактор всегда загружен, но показывается только при editorVisible = true
    Loader {
        id: editorLoader
        anchors.fill: parent
        active: true            // компонент создаётся сразу и живёт всё время
        visible: editorVisible

        sourceComponent: NoteEditPage {
            // noteId берётся из свойства window, обновляется при открытии
            noteId: window.currentNoteId

            onSaveClicked: {
                window.editorVisible = false
                notesListPage.refreshList()
            }
            onBackClicked: {
                window.editorVisible = false
                notesListPage.refreshList()
            }
        }
    }

    // Функция для открытия редактора с нужным id заметки
    function openEditor(noteId) {
        window.currentNoteId = noteId   // меняем свойство — NoteEditPage перехватит изменение
        window.editorVisible = true
    }
}