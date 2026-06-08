/****************************************************************************
** Meta object code from reading C++ file 'notemanager.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../1da9d33b4e9f55e043f17e03ccf6e3f7/notemanager.h"
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
        "filteredNotesChanged",
        "noteById",
        "Note",
        "id",
        "addOrUpdateNote",
        "note",
        "addOrUpdateNoteFields",
        "title",
        "content",
        "QColor",
        "color",
        "pinned",
        "removeNote",
        "togglePin",
        "filteredNotes",
        "QList<Note>",
        "notes",
        "searchQuery",
        "sortNewestFirst"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'notesChanged'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'searchQueryChanged'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'sortNewestFirstChanged'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'filteredNotesChanged'
        QtMocHelpers::SignalData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'noteById'
        QtMocHelpers::MethodData<Note(int) const>(6, 2, QMC::AccessPublic, 0x80000000 | 7, {{
            { QMetaType::Int, 8 },
        }}),
        // Method 'addOrUpdateNote'
        QtMocHelpers::MethodData<void(const Note &)>(9, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 7, 10 },
        }}),
        // Method 'addOrUpdateNoteFields'
        QtMocHelpers::MethodData<void(int, const QString &, const QString &, const QColor &, bool)>(11, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 8 }, { QMetaType::QString, 12 }, { QMetaType::QString, 13 }, { 0x80000000 | 14, 15 },
            { QMetaType::Bool, 16 },
        }}),
        // Method 'removeNote'
        QtMocHelpers::MethodData<void(int)>(17, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 8 },
        }}),
        // Method 'togglePin'
        QtMocHelpers::MethodData<void(int)>(18, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 8 },
        }}),
        // Method 'filteredNotes'
        QtMocHelpers::MethodData<QList<Note>() const>(19, 2, QMC::AccessPublic, 0x80000000 | 20),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'notes'
        QtMocHelpers::PropertyData<QList<Note>>(21, 0x80000000 | 20, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'searchQuery'
        QtMocHelpers::PropertyData<QString>(22, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 1),
        // property 'sortNewestFirst'
        QtMocHelpers::PropertyData<bool>(23, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 2),
        // property 'filteredNotes'
        QtMocHelpers::PropertyData<QList<Note>>(19, 0x80000000 | 20, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 3),
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
        case 3: _t->filteredNotesChanged(); break;
        case 4: { Note _r = _t->noteById((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast<Note*>(_a[0]) = std::move(_r); }  break;
        case 5: _t->addOrUpdateNote((*reinterpret_cast<std::add_pointer_t<Note>>(_a[1]))); break;
        case 6: _t->addOrUpdateNoteFields((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<QColor>>(_a[4])),(*reinterpret_cast<std::add_pointer_t<bool>>(_a[5]))); break;
        case 7: _t->removeNote((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 8: _t->togglePin((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 9: { QList<Note> _r = _t->filteredNotes();
            if (_a[0]) *reinterpret_cast<QList<Note>*>(_a[0]) = std::move(_r); }  break;
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
        if (QtMocHelpers::indexOfMethod<void (NoteManager::*)()>(_a, &NoteManager::filteredNotesChanged, 3))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QList<Note>*>(_v) = _t->notes(); break;
        case 1: *reinterpret_cast<QString*>(_v) = _t->searchQuery(); break;
        case 2: *reinterpret_cast<bool*>(_v) = _t->sortNewestFirst(); break;
        case 3: *reinterpret_cast<QList<Note>*>(_v) = _t->filteredNotes(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 1: _t->setSearchQuery(*reinterpret_cast<QString*>(_v)); break;
        case 2: _t->setSortNewestFirst(*reinterpret_cast<bool*>(_v)); break;
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
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 10;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
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
void NoteManager::filteredNotesChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
