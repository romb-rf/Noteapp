#include <gtest/gtest.h>
#include "notemanager.h"
#include <QTemporaryDir>
#include <QFile>
#include <QTextStream>
#include <QCoreApplication>
#include <utility>
class NoteManagerTest : public ::testing::Test {
protected:
    void SetUp() override {
        tempDir = std::make_unique<QTemporaryDir>();
        ASSERT_TRUE(tempDir->isValid());
        testFilePath = tempDir->path() + "/notes_test.json";
        manager = std::make_unique<NoteManager>();
        for (const auto& note : manager->notes()) {
            manager->removeNote(note.id());
        }
    }
    void TearDown() override {
        manager.reset();
        tempDir.reset();
    }
    int addTestNote(const QString& title, const QString& content, const QStringList& tags = {}) {
        manager->addOrUpdateNoteFields(-1, title, content, QColor(), false, tags, QDateTime());
        QList<Note> notes = manager->notes();
        if (notes.isEmpty()) return -1;
        return notes.last().id();
    }
    std::unique_ptr<QTemporaryDir> tempDir;
    QString testFilePath;
    std::unique_ptr<NoteManager> manager;
};
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
    const auto notes = loaded.notes();
    bool found1 = false, found2 = false;
    for (const Note& n : std::as_const(notes)) {
        if (n.title() == "Note1" && n.content() == "Content1" && n.tags() == QStringList({"tagA"}))
            found1 = true;
        if (n.title() == "Note2" && n.content() == "Content2" && n.tags() == QStringList({"tagB"}))
            found2 = true;
    }
    EXPECT_TRUE(found1);
    EXPECT_TRUE(found2);
}
TEST_F(NoteManagerTest, LoadFromCorruptedFile) {
    addTestNote("Good", "Good content");
    manager->saveToFile(testFilePath);
    QFile file(testFilePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        FAIL() << "Cannot open file for corruption";
    }
    file.write("This is not a JSON array");
    file.close();
    NoteManager loaded;
    bool result = loaded.loadFromFile(testFilePath);
    EXPECT_FALSE(result);
    EXPECT_EQ(loaded.notes().size(), 0);
}
TEST_F(NoteManagerTest, LoadFromMissingFile) {
    NoteManager loaded;
    QString missingPath = tempDir->path() + "/does_not_exist.json";
    bool result = loaded.loadFromFile(missingPath);
    EXPECT_FALSE(result);
    EXPECT_EQ(loaded.notes().size(), 0);
}
TEST_F(NoteManagerTest, AddAndUpdateNote) {
    manager->addOrUpdateNoteFields(-1, "New", "Content", QColor(), false, {}, QDateTime());
    auto notes = manager->notes();
    ASSERT_EQ(notes.size(), 1);
    int id = notes[0].id();
    EXPECT_GT(id, 0);
    EXPECT_EQ(notes[0].title(), "New");
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
    manager->removeNote(9999);
    EXPECT_EQ(manager->notes().size(), 1);
}
TEST_F(NoteManagerTest, TogglePin) {
    int id = addTestNote("Pin me", "content");
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
    manager->setSearchQuery("milk");
    auto filtered = manager->filteredNotes();
    ASSERT_EQ(filtered.size(), 1);
    EXPECT_EQ(filtered[0].title(), "Buy milk");
    manager->setSearchQuery("care");
    filtered = manager->filteredNotes();
    ASSERT_EQ(filtered.size(), 1);
    EXPECT_EQ(filtered[0].title(), "Walk dog");
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
    QSet<QString> titles;
    for (const auto& n : std::as_const(filtered)) titles.insert(n.title());
    EXPECT_TRUE(titles.contains("Note A"));
    EXPECT_TRUE(titles.contains("Note C"));
    EXPECT_FALSE(titles.contains("Note B"));
    manager->setTagFilter("nonexistent");
    EXPECT_EQ(manager->filteredNotes().size(), 0);
}
TEST_F(NoteManagerTest, FilteredNotesSorting) {
    QDateTime now = QDateTime::currentDateTime();
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
    EXPECT_GE(filtered[0].modified(), filtered[1].modified());
    EXPECT_GE(filtered[1].modified(), filtered[2].modified());
    manager->setSortNewestFirst(false);
    filtered = manager->filteredNotes();
    EXPECT_LE(filtered[0].modified(), filtered[1].modified());
    EXPECT_LE(filtered[1].modified(), filtered[2].modified());
}
TEST_F(NoteManagerTest, AllTags) {
    addTestNote("1", "", {"a", "b"});
    addTestNote("2", "", {"b", "c"});
    addTestNote("3", "", {"a"});
    auto tags = manager->allTags();
    EXPECT_EQ(tags.size(), 3);
    EXPECT_TRUE(tags.contains("a"));
    EXPECT_TRUE(tags.contains("b"));
    EXPECT_TRUE(tags.contains("c"));
}
TEST_F(NoteManagerTest, AddNoteEmptyTitle) {
    manager->addOrUpdateNoteFields(-1, "", "Empty title note", QColor(), false, {}, QDateTime());
    EXPECT_EQ(manager->notes().size(), 1);
    EXPECT_EQ(manager->notes()[0].title(), "");
}
TEST_F(NoteManagerTest, AddNoteLongContent) {
    QString longContent(10000, 'A');
    manager->addOrUpdateNoteFields(-1, "Long", longContent, QColor(), false, {}, QDateTime());
    EXPECT_EQ(manager->notes().size(), 1);
    EXPECT_EQ(manager->notes()[0].content().length(), 10000);
}
TEST_F(NoteManagerTest, RemoveAllNotes) {
    addTestNote("A", "a");
    addTestNote("B", "b");
    addTestNote("C", "c");
    EXPECT_EQ(manager->notes().size(), 3);
    for (const auto& note : manager->notes()) {
        manager->removeNote(note.id());
    }
    EXPECT_EQ(manager->notes().size(), 0);
}
TEST_F(NoteManagerTest, TogglePinNonExistent) {
    manager->togglePin(99999);
    EXPECT_EQ(manager->notes().size(), 0);
}
TEST_F(NoteManagerTest, FilterByMultipleTags) {
    addTestNote("Multi", "", {"work", "urgent", "important"});
    manager->setTagFilter("urgent");
    auto filtered = manager->filteredNotes();
    ASSERT_EQ(filtered.size(), 1);
    EXPECT_EQ(filtered[0].title(), "Multi");
}
TEST_F(NoteManagerTest, SearchCaseInsensitive) {
    addTestNote("Hello WORLD", "content");
    manager->setSearchQuery("world");
    auto filtered = manager->filteredNotes();
    EXPECT_EQ(filtered.size(), 1);
}
TEST_F(NoteManagerTest, SortPinnedFirst) {
    QDateTime now = QDateTime::currentDateTime();
    Note n1, n2;
    n1.setTitle("Pinned older");
    n1.setPinned(true);
    n1.setModified(now.addSecs(-100));
    n2.setTitle("Unpinned newer");
    n2.setPinned(false);
    n2.setModified(now.addSecs(-10));
    manager->addOrUpdateNote(n1);
    manager->addOrUpdateNote(n2);
    manager->setSortNewestFirst(true);
    auto filtered = manager->filteredNotes();
    ASSERT_EQ(filtered.size(), 2);
    EXPECT_TRUE(filtered[0].isPinned());
    EXPECT_FALSE(filtered[1].isPinned());
}
TEST_F(NoteManagerTest, SaveEmptyThenLoad) {
    manager->saveToFile(testFilePath);
    NoteManager newManager;
    EXPECT_TRUE(newManager.loadFromFile(testFilePath));
    EXPECT_EQ(newManager.notes().size(), 0);
}
TEST_F(NoteManagerTest, AllTagsEmpty) {
    EXPECT_TRUE(manager->allTags().isEmpty());
}