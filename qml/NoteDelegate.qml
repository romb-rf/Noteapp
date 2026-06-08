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

    // Тень
    layer.enabled: true


    // Цветовая полоска слева
    Rectangle {
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        width: 6
        color: modelData.color
    }

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

        // Кнопка закрепления
        ToolButton {
            text: modelData.pinned ? "📌" : "📍"
            font.pixelSize: 20
            onClicked: {
                console.log("Toggle pin for id:", modelData.id)  // для отладки
                noteManager.togglePin(modelData.id)
            }
        }
    }

    // Анимация нажатия
    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onClicked: delegateRoot.clicked()
        onPressed: delegateRoot.scale = 0.97
        onReleased: delegateRoot.scale = 1.0
    }

    Behavior on scale {
        NumberAnimation { duration: 150; easing.type: Easing.OutQuad }
    }
}