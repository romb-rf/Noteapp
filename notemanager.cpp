#include "notemanager.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <algorithm>
#include <QCoreApplication>
NoteManager::NoteManager(QObject *parent) : QObject(parent) {}

QList<Note> NoteManager::notes() const { return m_notes; }

QString NoteManager::searchQuery() const { return m_searchQuery; }
void NoteManager::setSearchQuery(const QString &query)
{
    if (m_searchQuery != query) {
        m_searchQuery = query;
        emit searchQueryChanged();
        emit notesChanged();
        emit filteredNotesChanged();
    }
}

bool NoteManager::sortNewestFirst() const { return m_sortNewestFirst; }
void NoteManager::setSortNewestFirst(bool value)
{
    if (m_sortNewestFirst != value) {
        m_sortNewestFirst = value;
        emit sortNewestFirstChanged();
        emit notesChanged();
        emit filteredNotesChanged();
    }
}

Note NoteManager::noteById(int id) const
{
    for (const auto &n : m_notes) {
        if (n.id() == id)
            return n;
    }
    return Note();
}

void NoteManager::addOrUpdateNote(const Note &note)
{
    Note mutableNote = note;
    if (mutableNote.id() < 0) {
        mutableNote.setCreated(QDateTime::currentDateTime());
        mutableNote.setModified(mutableNote.created());
        assignNewId(mutableNote);
        m_notes.append(mutableNote);
    } else {
        for (auto &n : m_notes) {
            if (n.id() == mutableNote.id()) {
                mutableNote.setCreated(n.created());
                mutableNote.setModified(QDateTime::currentDateTime());
                n = mutableNote;
                break;
            }
        }
    }
    emit notesChanged();
    emit filteredNotesChanged();
    // Автоматическое сохранение при изменениях (можно отключить, если не нужно)
    saveToFile(QCoreApplication::applicationDirPath() + "/notes.json");
}

void NoteManager::addOrUpdateNoteFields(int id, const QString &title,
                                        const QString &content, const QColor &color, bool pinned)
{
    Note note;
    note.setId(id);
    note.setTitle(title);
    note.setContent(content);
    note.setColor(color);
    note.setPinned(pinned);
    addOrUpdateNote(note);
}

void NoteManager::removeNote(int id)
{
    m_notes.erase(
        std::remove_if(m_notes.begin(), m_notes.end(),
                       [id](const Note &n) { return n.id() == id; }),
        m_notes.end());
    emit notesChanged();
    emit filteredNotesChanged();
    saveToFile(QCoreApplication::applicationDirPath() + "/notes.json");
}

void NoteManager::togglePin(int id)
{
    for (auto &n : m_notes) {
        if (n.id() == id) {
            n.setPinned(!n.isPinned());
            emit notesChanged();
            saveToFile(QCoreApplication::applicationDirPath() + "/notes.json");
            break;
        }
    }
    emit filteredNotesChanged();
}

QList<Note> NoteManager::filteredNotes() const
{
    QList<Note> result = m_notes;
    if (!m_searchQuery.isEmpty()) {
        QString query = m_searchQuery.toLower();
        result.erase(std::remove_if(result.begin(), result.end(),
                                    [&query](const Note &n) {
                                        return !n.title().toLower().contains(query) &&
                                               !n.content().toLower().contains(query);
                                    }), result.end());
    }
    std::sort(result.begin(), result.end(),
              [this](const Note &a, const Note &b) {
                  if (a.isPinned() != b.isPinned())
                      return a.isPinned();
                  if (m_sortNewestFirst)
                      return a.modified() > b.modified();
                  else
                      return a.modified() < b.modified();
              });
    return result;
}

bool NoteManager::loadFromFile(const QString &filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly))
        return false;
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();
    if (!doc.isArray())
        return false;
    m_notes.clear();
    for (const auto &val : doc.array()) {
        m_notes.append(Note(val.toObject()));
    }
    emit notesChanged();
    return true;
}

bool NoteManager::saveToFile(const QString &filename) const
{
    QJsonArray arr;
    for (const auto &n : m_notes)
        arr.append(n.toJson());
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly))
        return false;
    file.write(QJsonDocument(arr).toJson(QJsonDocument::Indented));
    file.close();
    return true;
}

void NoteManager::assignNewId(Note &note)
{
    note.setId(nextId());
}

int NoteManager::nextId() const
{
    int maxId = 0;
    for (const auto &n : m_notes)
        if (n.id() > maxId)
            maxId = n.id();
    return maxId + 1;
}