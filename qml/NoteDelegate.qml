import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: delegateRoot
    signal clicked()
    height: 80
    radius: 16
    color: "#323248"
    border.color: "#464660"
    clip: true

    layer.enabled: true


    // Общая область клика – на заднем плане, чтобы не перекрывать кнопку закрепления
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

    // Содержимое карточки
    RowLayout {
        anchors.fill: parent
        anchors.leftMargin: 18
        anchors.rightMargin: 12
        spacing: 12

        // Текстовая часть
        ColumnLayout {
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignVCenter
            spacing: 2

            Label {
                text: modelData.title || "Без названия"
                font.bold: true
                font.pixelSize: 16
                color: "#ffffff"
                elide: Text.ElideRight
                Layout.fillWidth: true
            }
            Label {
                text: modelData.content.length > 60
                      ? modelData.content.substring(0, 60) + "…"
                      : modelData.content
                font.pixelSize: 13
                color: "#b0b0d0"
                elide: Text.ElideRight
                Layout.fillWidth: true
                visible: text !== ""
            }
            Label {
                text: "🕒 " + new Date(modelData.modified).toLocaleString(Qt.locale(), "dd.MM.yyyy hh:mm")
                font.pixelSize: 11
                color: "#8888aa"
            }
        }

        // Кнопка закрепления (со своим обработчиком, поверх общей MouseArea)
        Rectangle {
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
    }

    // Анимация нажатия (можно оставить для красоты)
    Behavior on scale {
        NumberAnimation { duration: 150; easing.type: Easing.OutQuad }
    }
}