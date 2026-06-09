#ifndef NOTE_H
#define NOTE_H

#include <QString>
#include <QDateTime>
#include <QColor>
#include <QJsonObject>
#include <QStringList>

class Note
{
    Q_GADGET
    Q_PROPERTY(int id READ id WRITE setId)
    Q_PROPERTY(QString title READ title WRITE setTitle)
    Q_PROPERTY(QString content READ content WRITE setContent)
    Q_PROPERTY(QDateTime created READ created WRITE setCreated)
    Q_PROPERTY(QDateTime modified READ modified WRITE setModified)
    Q_PROPERTY(QColor color READ color WRITE setColor)
    Q_PROPERTY(bool pinned READ isPinned WRITE setPinned)
    Q_PROPERTY(QStringList tags READ tags WRITE setTags)
    Q_PROPERTY(QDateTime reminder READ reminder WRITE setReminder)

public:
    Note();
    Note(const QJsonObject &json);

    int id() const;
    void setId(int id);

    QString title() const;
    void setTitle(const QString &title);

    QString content() const;
    void setContent(const QString &content);

    QDateTime created() const;
    void setCreated(const QDateTime &created);

    QDateTime modified() const;
    void setModified(const QDateTime &modified);

    QColor color() const;
    void setColor(const QColor &color);

    bool isPinned() const;
    void setPinned(bool pinned);

    QStringList tags() const;
    void setTags(const QStringList &tags);

    QDateTime reminder() const;
    void setReminder(const QDateTime &reminder);

    QJsonObject toJson() const;

private:
    int m_id = -1;
    QString m_title;
    QString m_content;
    QDateTime m_created;
    QDateTime m_modified;
    QColor m_color = Qt::white;
    bool m_pinned = false;
    QStringList m_tags;
    QDateTime m_reminder;
};

#endif // NOTE_H