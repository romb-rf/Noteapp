/****************************************************************************
** Meta object code from reading C++ file 'notemanager.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../notemanager.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'notemanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.10.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN11NoteManagerE_t {};
} // unnamed namespace

template <> constexpr inline auto NoteManager::qt_create_metaobjectdata<qt_meta_tag_ZN11NoteManagerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "NoteManager",
        "notesChanged",
        "",
        "searchQueryChanged",
        "sortNewestFirstChanged",
        "tagFilterChanged",
        "filteredNotesChanged",
        "reminderTriggered",
        "Note",
        "note",
        "checkReminders",
        "noteById",
        "id",
        "addOrUpdateNote",
        "addOrUpdateNoteFields",
        "title",
        "content",
        "QColor",
        "color",
        "pinned",
        "tags",
        "reminder",
        "removeNote",
        "togglePin",
        "filteredNotes",
        "QList<Note>",
        "allTags",
        "highlightText",
        "text",
        "query",
        "notes",
        "searchQuery",
        "sortNewestFirst",
        "tagFilter"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'notesChanged'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'searchQueryChanged'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'sortNewestFirstChanged'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'tagFilterChanged'
        QtMocHelpers::SignalData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'filteredNotesChanged'
        QtMocHelpers::SignalData<void()>(6, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'reminderTriggered'
        QtMocHelpers::SignalData<void(const Note &)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 8, 9 },
        }}),
        // Slot 'checkReminders'
        QtMocHelpers::SlotData<void()>(10, 2, QMC::AccessPrivate, QMetaType::Void),
        // Method 'noteById'
        QtMocHelpers::MethodData<Note(int) const>(11, 2, QMC::AccessPublic, 0x80000000 | 8, {{
            { QMetaType::Int, 12 },
        }}),
        // Method 'addOrUpdateNote'
        QtMocHelpers::MethodData<void(const Note &)>(13, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 8, 9 },
        }}),
        // Method 'addOrUpdateNoteFields'
        QtMocHelpers::MethodData<void(int, const QString &, const QString &, const QColor &, bool, const QStringList &, const QDateTime &)>(14, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 12 }, { QMetaType::QString, 15 }, { QMetaType::QString, 16 }, { 0x80000000 | 17, 18 },
            { QMetaType::Bool, 19 }, { QMetaType::QStringList, 20 }, { QMetaType::QDateTime, 21 },
        }}),
        // Method 'removeNote'
        QtMocHelpers::MethodData<void(int)>(22, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 12 },
        }}),
        // Method 'togglePin'
        QtMocHelpers::MethodData<void(int)>(23, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 12 },
        }}),
        // Method 'filteredNotes'
        QtMocHelpers::MethodData<QList<Note>() const>(24, 2, QMC::AccessPublic, 0x80000000 | 25),
        // Method 'allTags'
        QtMocHelpers::MethodData<QStringList() const>(26, 2, QMC::AccessPublic, QMetaType::QStringList),
        // Method 'highlightText'
        QtMocHelpers::MethodData<QString(const QString &, const QString &) const>(27, 2, QMC::AccessPublic, QMetaType::QString, {{
            { QMetaType::QString, 28 }, { QMetaType::QString, 29 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'notes'
        QtMocHelpers::PropertyData<QList<Note>>(30, 0x80000000 | 25, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'searchQuery'
        QtMocHelpers::PropertyData<QString>(31, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 1),
        // property 'sortNewestFirst'
        QtMocHelpers::PropertyData<bool>(32, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 2),
        // property 'tagFilter'
        QtMocHelpers::PropertyData<QString>(33, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 3),
        // property 'filteredNotes'
        QtMocHelpers::PropertyData<QList<Note>>(24, 0x80000000 | 25, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 4),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<NoteManager, qt_meta_tag_ZN11NoteManagerE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject NoteManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11NoteManagerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11NoteManagerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN11NoteManagerE_t>.metaTypes,
    nullptr
} };

void NoteManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<NoteManager *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->notesChanged(); break;
        case 1: _t->searchQueryChanged(); break;
        case 2: _t->sortNewestFirstChanged(); break;
        case 3: _t->tagFilterChanged(); break;
        case 4: _t->filteredNotesChanged(); break;
        case 5: _t->reminderTriggered((*reinterpret_cast<std::add_pointer_t<Note>>(_a[1]))); break;
        case 6: _t->checkReminders(); break;
        case 7: { Note _r = _t->noteById((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast<Note*>(_a[0]) = std::move(_r); }  break;
        case 8: _t->addOrUpdateNote((*reinterpret_cast<std::add_pointer_t<Note>>(_a[1]))); break;
        case 9: _t->addOrUpdateNoteFields((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<QColor>>(_a[4])),(*reinterpret_cast<std::add_pointer_t<bool>>(_a[5])),(*reinterpret_cast<std::add_pointer_t<QStringList>>(_a[6])),(*reinterpret_cast<std::add_pointer_t<QDateTime>>(_a[7]))); break;
        case 10: _t->removeNote((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 11: _t->togglePin((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 12: { QList<Note> _r = _t->filteredNotes();
            if (_a[0]) *reinterpret_cast<QList<Note>*>(_a[0]) = std::move(_r); }  break;
        case 13: { QStringList _r = _t->allTags();
            if (_a[0]) *reinterpret_cast<QStringList*>(_a[0]) = std::move(_r); }  break;
        case 14: { QString _r = _t->highlightText((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])));
            if (_a[0]) *reinterpret_cast<QString*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (NoteManager::*)()>(_a, &NoteManager::notesChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (NoteManager::*)()>(_a, &NoteManager::searchQueryChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (NoteManager::*)()>(_a, &NoteManager::sortNewestFirstChanged, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (NoteManager::*)()>(_a, &NoteManager::tagFilterChanged, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (NoteManager::*)()>(_a, &NoteManager::filteredNotesChanged, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (NoteManager::*)(const Note & )>(_a, &NoteManager::reminderTriggered, 5))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QList<Note>*>(_v) = _t->notes(); break;
        case 1: *reinterpret_cast<QString*>(_v) = _t->searchQuery(); break;
        case 2: *reinterpret_cast<bool*>(_v) = _t->sortNewestFirst(); break;
        case 3: *reinterpret_cast<QString*>(_v) = _t->tagFilter(); break;
        case 4: *reinterpret_cast<QList<Note>*>(_v) = _t->filteredNotes(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 1: _t->setSearchQuery(*reinterpret_cast<QString*>(_v)); break;
        case 2: _t->setSortNewestFirst(*reinterpret_cast<bool*>(_v)); break;
        case 3: _t->setTagFilter(*reinterpret_cast<QString*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *NoteManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NoteManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11NoteManagerE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int NoteManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 15;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void NoteManager::notesChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void NoteManager::searchQueryChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void NoteManager::sortNewestFirstChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void NoteManager::tagFilterChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void NoteManager::filteredNotesChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void NoteManager::reminderTriggered(const Note & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 5, nullptr, _t1);
}
QT_WARNING_POP
