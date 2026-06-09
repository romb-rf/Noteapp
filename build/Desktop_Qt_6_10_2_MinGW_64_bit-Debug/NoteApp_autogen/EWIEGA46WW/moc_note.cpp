/****************************************************************************
** Meta object code from reading C++ file 'note.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../note.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'note.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN4NoteE_t {};
} // unnamed namespace

template <> constexpr inline auto Note::qt_create_metaobjectdata<qt_meta_tag_ZN4NoteE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Note",
        "id",
        "title",
        "content",
        "created",
        "modified",
        "color",
        "QColor",
        "pinned",
        "tags",
        "reminder"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
        // property 'id'
        QtMocHelpers::PropertyData<int>(1, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'title'
        QtMocHelpers::PropertyData<QString>(2, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'content'
        QtMocHelpers::PropertyData<QString>(3, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'created'
        QtMocHelpers::PropertyData<QDateTime>(4, QMetaType::QDateTime, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'modified'
        QtMocHelpers::PropertyData<QDateTime>(5, QMetaType::QDateTime, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'color'
        QtMocHelpers::PropertyData<QColor>(6, 0x80000000 | 7, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet),
        // property 'pinned'
        QtMocHelpers::PropertyData<bool>(8, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'tags'
        QtMocHelpers::PropertyData<QStringList>(9, QMetaType::QStringList, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
        // property 'reminder'
        QtMocHelpers::PropertyData<QDateTime>(10, QMetaType::QDateTime, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<Note, qt_meta_tag_ZN4NoteE_t>(QMC::PropertyAccessInStaticMetaCall, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Note::staticMetaObject = { {
    nullptr,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN4NoteE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN4NoteE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN4NoteE_t>.metaTypes,
    nullptr
} };

void Note::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = reinterpret_cast<Note *>(_o);
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<int*>(_v) = _t->id(); break;
        case 1: *reinterpret_cast<QString*>(_v) = _t->title(); break;
        case 2: *reinterpret_cast<QString*>(_v) = _t->content(); break;
        case 3: *reinterpret_cast<QDateTime*>(_v) = _t->created(); break;
        case 4: *reinterpret_cast<QDateTime*>(_v) = _t->modified(); break;
        case 5: *reinterpret_cast<QColor*>(_v) = _t->color(); break;
        case 6: *reinterpret_cast<bool*>(_v) = _t->isPinned(); break;
        case 7: *reinterpret_cast<QStringList*>(_v) = _t->tags(); break;
        case 8: *reinterpret_cast<QDateTime*>(_v) = _t->reminder(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setId(*reinterpret_cast<int*>(_v)); break;
        case 1: _t->setTitle(*reinterpret_cast<QString*>(_v)); break;
        case 2: _t->setContent(*reinterpret_cast<QString*>(_v)); break;
        case 3: _t->setCreated(*reinterpret_cast<QDateTime*>(_v)); break;
        case 4: _t->setModified(*reinterpret_cast<QDateTime*>(_v)); break;
        case 5: _t->setColor(*reinterpret_cast<QColor*>(_v)); break;
        case 6: _t->setPinned(*reinterpret_cast<bool*>(_v)); break;
        case 7: _t->setTags(*reinterpret_cast<QStringList*>(_v)); break;
        case 8: _t->setReminder(*reinterpret_cast<QDateTime*>(_v)); break;
        default: break;
        }
    }
}
QT_WARNING_POP
