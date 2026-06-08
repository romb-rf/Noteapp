import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    id: window
    visible: true
    width: 420
    height: 720
    title: "Заметки"
    color: "#1e1e2e"   // глубокий тёмный фон

    // Кастомные анимации переходов между страницами
    StackView {
        id: stackView
        anchors.fill: parent

        pushEnter: Transition {
            ParallelAnimation {
                NumberAnimation { property: "x"; from: stackView.width; to: 0; duration: 300; easing.type: Easing.OutCubic }
                NumberAnimation { property: "opacity"; from: 0.0; to: 1.0; duration: 300 }
            }
        }
        pushExit: Transition {
            NumberAnimation { property: "opacity"; from: 1.0; to: 0.0; duration: 200 }
        }
        popEnter: Transition {
            NumberAnimation { property: "x"; from: -stackView.width/3; to: 0; duration: 300; easing.type: Easing.OutCubic }
        }
        popExit: Transition {
            NumberAnimation { property: "x"; from: 0; to: stackView.width; duration: 300; easing.type: Easing.InCubic }
        }

        initialItem: notesListPage
    }

    Component {
        id: notesListPage
        NotesListPage {}
    }
    Component {
        id: noteEditPage
        NoteEditPage {}
    }
}