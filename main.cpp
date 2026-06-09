#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>          // ← заменили <QtQuickControls2>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QIcon>
#include <QTimer>
#include <QCoreApplication>
#include "notemanager.h"
#include "note.h"

// ... остальной код без изменений

// Вспомогательный класс для взаимодействия с треем из QML
class TrayHelper : public QObject
{
    Q_OBJECT
public:
    explicit TrayHelper(QSystemTrayIcon *tray, QWindow *win, QObject *parent = nullptr)
        : QObject(parent), m_tray(tray), m_window(win) {}

    Q_INVOKABLE void hideWindow() {
        if (m_window) {
            m_window->hide();
            m_tray->showMessage("Заметки", "Приложение свёрнуто в трей. Напоминания работают.",
                                QSystemTrayIcon::Information, 2000);
        }
    }

    Q_INVOKABLE void showWindow() {
        if (m_window) {
            m_window->show();
            m_window->raise();
            m_window->requestActivate();
        }
    }

private:
    QSystemTrayIcon *m_tray;
    QWindow *m_window;
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);      // <-- QApplication вместо QGuiApplication
    app.setQuitOnLastWindowClosed(false);

    QQuickStyle::setStyle("Basic");

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

    // Получаем корневое окно
    QObject *rootObject = engine.rootObjects().value(0);
    QWindow *window = qobject_cast<QWindow*>(rootObject);

    // Системный трей
    QSystemTrayIcon *trayIcon = new QSystemTrayIcon(&app);
    trayIcon->setIcon(QIcon(":/qt-project.org/qmessagebox/images/qtlogo-64.png"));  // можно заменить на свой ресурс
    trayIcon->setToolTip("Заметки");

    QMenu *trayMenu = new QMenu();
    QAction *showAction = trayMenu->addAction("Показать");
    QAction *quitAction = trayMenu->addAction("Выход");
    trayIcon->setContextMenu(trayMenu);

    // Создаём помощник для трея и передаём в QML
    TrayHelper *trayHelper = new TrayHelper(trayIcon, window, &app);
    engine.rootContext()->setContextProperty("trayHelper", trayHelper);

    QObject::connect(showAction, &QAction::triggered, [trayHelper]() {
        trayHelper->showWindow();
    });

    QObject::connect(quitAction, &QAction::triggered, &app, &QCoreApplication::quit);

    trayIcon->show();

    // Напоминания
    QObject::connect(&manager, &NoteManager::reminderTriggered,
                     [&manager, trayIcon, window](const Note &note) {
                         QString title = note.title().isEmpty() ? "Без названия" : note.title();
                         QString body = note.content().left(100);
                         trayIcon->showMessage("⏰ " + title, body, QSystemTrayIcon::Information, 5000);

                         if (window && window->isVisible()) {
                             QMetaObject::invokeMethod(window, "showToast",
                                                       Q_ARG(QVariant, title),
                                                       Q_ARG(QVariant, body));
                         }
                     });

    // Двойной клик по иконке трея – показать окно
    QObject::connect(trayIcon, &QSystemTrayIcon::activated,
                     [trayHelper](QSystemTrayIcon::ActivationReason reason) {
                         if (reason == QSystemTrayIcon::DoubleClick)
                             trayHelper->showWindow();
                     });

    int ret = app.exec();
    manager.saveToFile(jsonPath);
    return ret;
}

#include "main.moc"