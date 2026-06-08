#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDir>
#include "notemanager.h"
#include "note.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    // Регистрируем тип Note (имя начинается со строчной буквы, иначе ошибка QML)
    qmlRegisterUncreatableType<Note>("NoteApp", 1, 0, "note",
                                     "Note is provided by NoteManager");

    NoteManager manager;
    // JSON будет сохраняться рядом с исполняемым файлом (или в рабочем каталоге)
    QString jsonPath = QCoreApplication::applicationDirPath() + "/notes.json";
    manager.loadFromFile(jsonPath);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("noteManager", &manager);

    // Загружаем главный QML из файловой системы
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