#include "note.h"
#include <QJsonArray>

Note::Note() = default;

Note::Note(const QJsonObject &json)
{
    m_id = json.value("id").toInt(-1);
    m_title = json.value("title").toString();
    m_content = json.value("content").toString();
    m_created = QDateTime::fromString(json.value("created").toString(), Qt::ISODate);
    m_modified = QDateTime::fromString(json.value("modified").toString(), Qt::ISODate);
    if (json.contains("color"))
        m_color = QColor(json.value("color").toString());
    m_pinned = json.value("pinned").toBool(false);
}

int Note::id() const { return m_id; }
void Note::setId(int id) { m_id = id; }

QString Note::title() const { return m_title; }
void Note::setTitle(const QString &title) { m_title = title; }

QString Note::content() const { return m_content; }
void Note::setContent(const QString &content) { m_content = content; }

QDateTime Note::created() const { return m_created; }
void Note::setCreated(const QDateTime &created) { m_created = created; }

QDateTime Note::modified() const { return m_modified; }
void Note::setModified(const QDateTime &modified) { m_modified = modified; }

QColor Note::color() const { return m_color; }
void Note::setColor(const QColor &color) { m_color = color; }

bool Note::isPinned() const { return m_pinned; }
void Note::setPinned(bool pinned) { m_pinned = pinned; }

QJsonObject Note::toJson() const
{
    QJsonObject obj;
    obj["id"] = m_id;
    obj["title"] = m_title;
    obj["content"] = m_content;
    obj["created"] = m_created.toString(Qt::ISODate);
    obj["modified"] = m_modified.toString(Qt::ISODate);
    obj["color"] = m_color.name(QColor::HexRgb);
    obj["pinned"] = m_pinned;
    return obj;
}