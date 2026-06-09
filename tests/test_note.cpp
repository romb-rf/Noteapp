#include <gtest/gtest.h>
#include "notemanager.h"
#include <QTemporaryDir>
#include <QFile>
#include <QTextStream>
#include <QCoreApplication>

class NoteManagerTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Создаём временную директорию для тестовых файлов
        tempDir = std::make_unique<QTemporaryDir>();
        ASSERT_TRUE(tempDir->isValid());
        testFilePath = tempDir->path() + "/notes_test.json";
        // Убеждаемся, что менеджер пуст
        manager = std::make_unique<NoteManager>();
        // Очищаем все заметки (через публичный API, если есть; пока нет clearAll, используем removeNote для каждой)
        for (const auto& note : manager->notes()) {
            manager->removeNote(note.id());
        }
    }

    void TearDown() override {
        manager.reset();
        tempDir.reset();
    }

    // Утилита: добавляет заметку и возвращает её ID (int)
    int addTestNote(const QString& title, const QString& content, const QStringList& tags = {}) {
        manager->addOrUpdateNoteFields(-1, title, content, QColor(), false, tags, QDateTime());
        // Последняя добавленная заметка – последняя в списке
        QList<Note> notes = manager->notes();
        if (notes.isEmpty()) return -1;
        return notes.last().id();
    }

    std::unique_ptr<QTemporaryDir> tempDir;
    QString testFilePath;
    std::unique_ptr<NoteManager> manager;
};

// ----- Тесты сохранения и загрузки -----

TEST_F(NoteManagerTest, SaveAndLoadEmptyFile) {
    EXPECT_TRUE(manager->saveToFile(testFilePath));
    EXPECT_TRUE(QFile::exists(testFilePath));

    NoteManager newManager;
    EXPECT_TRUE(newManager.loadFromFile(testFilePath));
    EXPECT_EQ(newManager.notes().size(), 0);
}

TEST_F(NoteManagerTest, SaveAndLoadWithNotes) {
    addTestNote("Note1", "Content1", {"tagA"});
    addTestNote("Note2", "Content2", {"tagB"});
    EXPECT_EQ(manager->notes().size(), 2);

    EXPECT_TRUE(manager->saveToFile(testFilePath));

    NoteManager loaded;
    EXPECT_TRUE(loaded.loadFromFile(testFilePath));
    EXPECT_EQ(loaded.notes().size(), 2);

    // Проверяем содержимое (порядок может быть не гарантирован, ищем по заголовку)
    auto notes = loaded.notes();
    bool found1 = false, found2 = false;
    for (const auto& n : notes) {
        if (n.title() == "Note1" && n.content() == "Content1" && n.tags() == QStringList({"tagA"}))
            found1 = true;
        if (n.title() == "Note2" && n.content() == "Content2" && n.tags() == QStringList({"tagB"}))
            found2 = true;
    }
    EXPECT_TRUE(found1);
    EXPECT_TRUE(found2);
}

TEST_F(NoteManagerTest, LoadFromCorruptedFile) {
    // Сохраняем нормальный файл
    addTestNote("Good", "Good content");
    manager->saveToFile(testFilePath);

    // Повреждаем файл
    QFile file(testFilePath);
    file.open(QIODevice::WriteOnly | QIODevice::Truncate);
    file.write("This is not a JSON array");
    file.close();

    NoteManager loaded;
    // Ожидаем, что load вернёт false, а заметки в loaded станут пустыми (согласно реализации)
    bool result = loaded.loadFromFile(testFilePath);
    EXPECT_FALSE(result);
    // По коду loadFromFile очищает m_notes перед разбором, поэтому после ошибки заметок нет
    EXPECT_EQ(loaded.notes().size(), 0);
}

TEST_F(NoteManagerTest, LoadFromMissingFile) {
    NoteManager loaded;
    QString missingPath = tempDir->path() + "/does_not_exist.json";
    bool result = loaded.loadFromFile(missingPath);
    EXPECT_FALSE(result);
    // При отсутствии файла m_notes не очищается (сохраняется старый пустой вектор)
    EXPECT_EQ(loaded.notes().size(), 0);
}

// ----- Тесты основных операций -----

TEST_F(NoteManagerTest, AddAndUpdateNote) {
    // Добавляем новую
    manager->addOrUpdateNoteFields(-1, "New", "Content", QColor(), false, {}, QDateTime());
    auto notes = manager->notes();
    ASSERT_EQ(notes.size(), 1);
    int id = notes[0].id();
    EXPECT_GT(id, 0);
    EXPECT_EQ(notes[0].title(), "New");

    // Обновляем ту же заметку
    manager->addOrUpdateNoteFields(id, "Updated", "NewContent", QColor(), true, {"tag"}, QDateTime());
    notes = manager->notes();
    ASSERT_EQ(notes.size(), 1);
    EXPECT_EQ(notes[0].title(), "Updated");
    EXPECT_EQ(notes[0].content(), "NewContent");
    EXPECT_TRUE(notes[0].isPinned());
    EXPECT_EQ(notes[0].tags(), QStringList({"tag"}));
}

TEST_F(NoteManagerTest, RemoveNote) {
    int id1 = addTestNote("One", "1");
    int id2 = addTestNote("Two", "2");
    EXPECT_EQ(manager->notes().size(), 2);

    manager->removeNote(id1);
    EXPECT_EQ(manager->notes().size(), 1);
    EXPECT_EQ(manager->notes()[0].id(), id2);

    manager->removeNote(9999); // несуществующий
    EXPECT_EQ(manager->notes().size(), 1);
}

TEST_F(NoteManagerTest, TogglePin) {
    int id = addTestNote("Pin me", "content");
    // По умолчанию не закреплена
    EXPECT_FALSE(manager->noteById(id).isPinned());

    manager->togglePin(id);
    EXPECT_TRUE(manager->noteById(id).isPinned());

    manager->togglePin(id);
    EXPECT_FALSE(manager->noteById(id).isPinned());
}

TEST_F(NoteManagerTest, FilteredNotesSearch) {
    addTestNote("Buy milk", "reminder", {"shopping"});
    addTestNote("Walk dog", "pet care", {"health"});
    addTestNote("Read book", "learning", {"study"});

    // Поиск по слову "milk" – должно найти только первую
    manager->setSearchQuery("milk");
    auto filtered = manager->filteredNotes();
    ASSERT_EQ(filtered.size(), 1);
    EXPECT_EQ(filtered[0].title(), "Buy milk");

    // Поиск по содержимому "care"
    manager->setSearchQuery("care");
    filtered = manager->filteredNotes();
    ASSERT_EQ(filtered.size(), 1);
    EXPECT_EQ(filtered[0].title(), "Walk dog");

    // Пустой поиск – все три
    manager->setSearchQuery("");
    filtered = manager->filteredNotes();
    EXPECT_EQ(filtered.size(), 3);
}

TEST_F(NoteManagerTest, FilteredNotesTagFilter) {
    addTestNote("Note A", "", {"work"});
    addTestNote("Note B", "", {"personal"});
    addTestNote("Note C", "", {"work", "urgent"});

    manager->setTagFilter("work");
    auto filtered = manager->filteredNotes();
    ASSERT_EQ(filtered.size(), 2);
    // ожидаем Note A и Note C
    QSet<QString> titles;
    for (const auto& n : filtered) titles.insert(n.title());
    EXPECT_TRUE(titles.contains("Note A"));
    EXPECT_TRUE(titles.contains("Note C"));
    EXPECT_FALSE(titles.contains("Note B"));

    manager->setTagFilter("nonexistent");
    EXPECT_EQ(manager->filteredNotes().size(), 0);
}

TEST_F(NoteManagerTest, FilteredNotesSorting) {
    QDateTime now = QDateTime::currentDateTime();
    // Добавляем заметки с разным modified (сдвигаем время)
    auto addWithModified = [&](const QString& title, int secondsAgo) {
        Note n;
        n.setTitle(title);
        n.setModified(now.addSecs(-secondsAgo));
        manager->addOrUpdateNote(n);
    };
    addWithModified("Old", 100);
    addWithModified("Newer", 10);
    addWithModified("Newest", 1);

    manager->setSortNewestFirst(true);
    auto filtered = manager->filteredNotes();
    ASSERT_EQ(filtered.size(), 3);
    EXPECT_EQ(filtered[0].title(), "Newest");
    EXPECT_EQ(filtered[2].title(), "Old");

    manager->setSortNewestFirst(false);
    filtered = manager->filteredNotes();
    EXPECT_EQ(filtered[0].title(), "Old");
    EXPECT_EQ(filtered[2].title(), "Newest");
}

TEST_F(NoteManagerTest, AllTags) {
    addTestNote("1", "", {"a", "b"});
    addTestNote("2", "", {"b", "c"});
    addTestNote("3", "", {"a"});
    auto tags = manager->allTags();
    // Порядок не важен
    EXPECT_EQ(tags.size(), 3);
    EXPECT_TRUE(tags.contains("a"));
    EXPECT_TRUE(tags.contains("b"));
    EXPECT_TRUE(tags.contains("c"));
}

TEST_F(NoteManagerTest, HighlightText) {
    QString text = "This is a test message for highlight";
    // Подсветка "test" должна обернуть в <b>
    QString highlighted = manager->highlightText(text, "test");
    EXPECT_TRUE(highlighted.contains("<b>test</b>"));
    EXPECT_FALSE(highlighted.contains("<b>message</b>")); // "message" не запрашивали

    // Регистронезависимость
    highlighted = manager->highlightText(text, "Test");
    EXPECT_TRUE(highlighted.contains("<b>test</b>"));

    // Пустой запрос – экранирование HTML
    highlighted = manager->highlightText("<script>alert('xss')</script>", "");
    // Должен быть экранирован
    EXPECT_TRUE(highlighted.contains("&lt;script&gt;alert(&apos;xss&apos;)&lt;/script&gt;"));
}