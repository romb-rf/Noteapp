import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Effects

Rectangle {
    id: delegateRoot
    signal clicked()
    height: 90
    radius: 16
    color: "#323248"
    border.color: "#464660"
    clip: true

    layer.enabled: true


    // Кликабельная область для открытия заметки
    MouseArea {
        id: cardMouseArea
        anchors.fill: parent
        onClicked: delegateRoot.clicked()
    }

    // Цветовая полоска слева
    Rectangle {
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        width: 6
        color: modelData.color
    }

    // Кнопка закрепления (всегда справа)
    Rectangle {
        id: pinButton
        anchors.right: parent.right
        anchors.rightMargin: 12
        anchors.verticalCenter: parent.verticalCenter
        width: 40; height: 40; radius: 8
        color: pinMouse.pressed ? "#4a4a6a" : "transparent"

        Text {
            anchors.centerIn: parent
            text: modelData.pinned ? "📌" : "📍"
            font.pixelSize: 20
        }

        MouseArea {
            id: pinMouse
            anchors.fill: parent
            onClicked: noteManager.togglePin(modelData.id)
        }
    }

    // Текстовая часть – теперь привязана к левой стороне кнопки с отступом 12
    Column {
        anchors.left: parent.left
        anchors.leftMargin: 18
        anchors.right: pinButton.left      // <-- ключевое изменение
        anchors.rightMargin: 12
        anchors.verticalCenter: parent.verticalCenter
        spacing: 2

        // Заголовок
        Text {
            width: parent.width
            text: {
                var t = modelData.title
                if (t && t.length > 0)
                    return noteManager.highlightText(t, noteManager.searchQuery)
                else
                    return "<i>Без названия</i>"
            }
            font.bold: true
            font.pixelSize: 16
            color: "#ffffff"
            textFormat: Text.RichText
            elide: Text.ElideRight
        }

        // Содержимое (с ограничением длины)
        Text {
            width: parent.width
            text: {
                var c = modelData.content
                if (!c || c.length === 0) return ""
                var shortContent = c.length > 80 ? c.substring(0, 80) + "…" : c
                return noteManager.highlightText(shortContent, noteManager.searchQuery)
            }
            font.pixelSize: 13
            color: "#b0b0d0"
            textFormat: Text.RichText
            elide: Text.ElideRight
            visible: modelData.content !== undefined && modelData.content !== ""
        }

        // Теги
        Row {
            spacing: 4
            visible: modelData.tags && modelData.tags.length > 0
            Repeater {
                model: modelData.tags
                Rectangle {
                    radius: 4
                    color: "#3d3d5c"
                    implicitWidth: tagText.implicitWidth + 10
                    implicitHeight: 18
                    Text {
                        id: tagText
                        anchors.centerIn: parent
                        text: modelData
                        font.pixelSize: 10
                        color: "#a0a0c0"
                    }
                }
            }
        }

        // Дата изменения
        Label {
            text: "🕒 " + new Date(modelData.modified).toLocaleString(Qt.locale(), "dd.MM.yyyy hh:mm")
            font.pixelSize: 11
            color: "#8888aa"
        }
    }

    Behavior on scale {
        NumberAnimation { duration: 150; easing.type: Easing.OutQuad }
    }
}