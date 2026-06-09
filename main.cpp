#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtQuickControls2>     // вместо QQuickStyle
#include <QCoreApplication>
#include "notemanager.h"
#include "note.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    // Устанавливаем стиль Basic, чтобы можно было менять фон у контролов
    QQuickStyle::setStyle("Basic");

    // Регистрируем тип Note
    qmlRegisterUncreatableType<Note>("NoteApp", 1, 0, "note",
                                     "Note is provided by NoteManager");

    NoteManager manager;
    QString jsonPath = QCoreApplication::applicationDirPath() + "/notes.json";
    manager.loadFromFile(jsonPath);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("noteManager", &manager);

    QString mainQml = QCoreApplication::applicationDirPath() + "/qml/main.qml";
    const QUrl url = QUrl::fromLocalFile(mainQml);

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
                         if (!obj && url == objUrl)
                             QCoreApplication::exit(-1);
                     }, Qt::QueuedConnection);
    engine.load(url);

    int ret = app.exec();
    manager.saveToFile(jsonPath);
    return ret;
}