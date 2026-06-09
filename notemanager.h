#ifndef NOTEMANAGER_H
#define NOTEMANAGER_H

#include <QObject>
#include <QTimer>
#include <QList>
#include "note.h"

class NoteManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<Note> notes READ notes NOTIFY notesChanged)
    Q_PROPERTY(QString searchQuery READ searchQuery WRITE setSearchQuery NOTIFY searchQueryChanged)
    Q_PROPERTY(bool sortNewestFirst READ sortNewestFirst WRITE setSortNewestFirst NOTIFY sortNewestFirstChanged)
    Q_PROPERTY(QString tagFilter READ tagFilter WRITE setTagFilter NOTIFY tagFilterChanged)
    Q_PROPERTY(QList<Note> filteredNotes READ filteredNotes NOTIFY filteredNotesChanged)

public:
    explicit NoteManager(QObject *parent = nullptr);

    QList<Note> notes() const;
    QString searchQuery() const;
    bool sortNewestFirst() const;
    QString tagFilter() const;

    void setSearchQuery(const QString &query);
    void setSortNewestFirst(bool value);
    void setTagFilter(const QString &tag);

    Q_INVOKABLE Note noteById(int id) const;
    Q_INVOKABLE void addOrUpdateNote(const Note &note);
    Q_INVOKABLE void addOrUpdateNoteFields(int id, const QString &title,
                                           const QString &content, const QColor &color, bool pinned,
                                           const QStringList &tags,
                                           const QDateTime &reminder);
    Q_INVOKABLE void removeNote(int id);
    Q_INVOKABLE void togglePin(int id);

    Q_INVOKABLE QList<Note> filteredNotes() const;
    Q_INVOKABLE QStringList allTags() const;
    Q_INVOKABLE QString highlightText(const QString &text, const QString &query) const;   // обязательно Q_INVOKABLE

    bool loadFromFile(const QString &filename);
    bool saveToFile(const QString &filename) const;

signals:
    void notesChanged();
    void searchQueryChanged();
    void sortNewestFirstChanged();
    void tagFilterChanged();
    void filteredNotesChanged();
    void reminderTriggered(const Note &note);

private slots:
    void checkReminders();

private:
    void assignNewId(Note &note);
    int nextId() const;

    QList<Note> m_notes;
    QString m_searchQuery;
    bool m_sortNewestFirst = true;
    QString m_tagFilter;
    QTimer *m_reminderTimer;
};

#endif // NOTEMANAGER_H