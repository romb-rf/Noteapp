#include <gtest/gtest.h>
#include "note.h"
#include <QJsonObject>
#include <QColor>

class NoteTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Инициализация перед каждым тестом
    }
};

TEST_F(NoteTest, DefaultConstructor) {
    Note n;
    EXPECT_EQ(n.id(), -1);
    EXPECT_TRUE(n.title().isEmpty());
    EXPECT_TRUE(n.content().isEmpty());
    EXPECT_EQ(n.color(), QColor());
    EXPECT_FALSE(n.isPinned());
    EXPECT_TRUE(n.tags().isEmpty());
    EXPECT_FALSE(n.reminder().isValid());
    EXPECT_TRUE(n.created().isNull());
    EXPECT_TRUE(n.modified().isNull());
}

TEST_F(NoteTest, SetFields) {
    Note n;
    n.setId(42);
    n.setTitle("Test title");
    n.setContent("Some content");
    n.setColor(Qt::red);
    n.setPinned(true);
    n.setTags({"work", "important"});
    QDateTime dt = QDateTime::currentDateTime();
    n.setReminder(dt);
    n.setCreated(dt);
    n.setModified(dt);

    EXPECT_EQ(n.id(), 42);
    EXPECT_EQ(n.title(), "Test title");
    EXPECT_EQ(n.content(), "Some content");
    EXPECT_EQ(n.color(), Qt::red);
    EXPECT_TRUE(n.isPinned());
    EXPECT_EQ(n.tags(), QStringList({"work", "important"}));
    EXPECT_EQ(n.reminder(), dt);
    EXPECT_EQ(n.created(), dt);
    EXPECT_EQ(n.modified(), dt);
}

TEST_F(NoteTest, ToJsonAndFromJson) {
    Note original;
    original.setId(10);
    original.setTitle("Json test");
    original.setContent("Content with special chars: \" \\ /");
    original.setColor(QColor(255, 128, 0));
    original.setPinned(true);
    original.setTags({"tag1", "tag2"});
    original.setReminder(QDateTime(QDate(2025, 12, 31), QTime(23, 59, 59)));

    QJsonObject json = original.toJson();
    Note restored(json);

    EXPECT_EQ(restored.id(), original.id());
    EXPECT_EQ(restored.title(), original.title());
    EXPECT_EQ(restored.content(), original.content());
    EXPECT_EQ(restored.color(), original.color());
    EXPECT_EQ(restored.isPinned(), original.isPinned());
    EXPECT_EQ(restored.tags(), original.tags());
    EXPECT_EQ(restored.reminder(), original.reminder());
    // created/modified не сохраняются в toJson? Если нет – то будут по умолчанию, надо проверить.
    // В вашей реализации toJson, вероятно, не сохраняет created/modified. Тест это покажет.
}