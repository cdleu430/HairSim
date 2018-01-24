/****************************************************************************
** Meta object code from reading C++ file 'NGLScene.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/NGLScene.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'NGLScene.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_NGLScene_t {
    QByteArrayData data[15];
    char stringdata0[142];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NGLScene_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NGLScene_t qt_meta_stringdata_NGLScene = {
    {
QT_MOC_LITERAL(0, 0, 8), // "NGLScene"
QT_MOC_LITERAL(1, 9, 15), // "toggleWireframe"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 5), // "_mode"
QT_MOC_LITERAL(4, 32, 11), // "setDrawMode"
QT_MOC_LITERAL(5, 44, 2), // "_i"
QT_MOC_LITERAL(6, 47, 8), // "resetSim"
QT_MOC_LITERAL(7, 56, 13), // "setGuideCount"
QT_MOC_LITERAL(8, 70, 6), // "_count"
QT_MOC_LITERAL(9, 77, 14), // "setFollowCount"
QT_MOC_LITERAL(10, 92, 13), // "setHairLength"
QT_MOC_LITERAL(11, 106, 7), // "_length"
QT_MOC_LITERAL(12, 114, 10), // "setHairLOD"
QT_MOC_LITERAL(13, 125, 4), // "_lod"
QT_MOC_LITERAL(14, 130, 11) // "toggleFocus"

    },
    "NGLScene\0toggleWireframe\0\0_mode\0"
    "setDrawMode\0_i\0resetSim\0setGuideCount\0"
    "_count\0setFollowCount\0setHairLength\0"
    "_length\0setHairLOD\0_lod\0toggleFocus"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NGLScene[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x0a /* Public */,
       4,    1,   57,    2, 0x0a /* Public */,
       6,    0,   60,    2, 0x0a /* Public */,
       7,    1,   61,    2, 0x0a /* Public */,
       9,    1,   64,    2, 0x0a /* Public */,
      10,    1,   67,    2, 0x0a /* Public */,
      12,    1,   70,    2, 0x0a /* Public */,
      14,    0,   73,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::Int,   13,
    QMetaType::Void,

       0        // eod
};

void NGLScene::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        NGLScene *_t = static_cast<NGLScene *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->toggleWireframe((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->setDrawMode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->resetSim(); break;
        case 3: _t->setGuideCount((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->setFollowCount((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->setHairLength((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->setHairLOD((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->toggleFocus(); break;
        default: ;
        }
    }
}

const QMetaObject NGLScene::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_NGLScene.data,
      qt_meta_data_NGLScene,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *NGLScene::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NGLScene::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_NGLScene.stringdata0))
        return static_cast<void*>(const_cast< NGLScene*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int NGLScene::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
