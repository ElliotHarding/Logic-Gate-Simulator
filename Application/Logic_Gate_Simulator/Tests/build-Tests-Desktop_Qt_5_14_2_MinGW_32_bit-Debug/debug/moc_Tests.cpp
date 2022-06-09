/****************************************************************************
** Meta object code from reading C++ file 'Tests.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../Tests/Tests.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Tests.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Tests_t {
    QByteArrayData data[15];
    char stringdata0[187];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Tests_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Tests_t qt_meta_stringdata_Tests = {
    {
QT_MOC_LITERAL(0, 0, 5), // "Tests"
QT_MOC_LITERAL(1, 6, 12), // "test_andGate"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 11), // "test_orGate"
QT_MOC_LITERAL(4, 32, 12), // "test_notGate"
QT_MOC_LITERAL(5, 45, 12), // "test_eorGate"
QT_MOC_LITERAL(6, 58, 12), // "test_xorGate"
QT_MOC_LITERAL(7, 71, 12), // "test_norGate"
QT_MOC_LITERAL(8, 84, 13), // "test_nandGate"
QT_MOC_LITERAL(9, 98, 15), // "test_triAndGate"
QT_MOC_LITERAL(10, 114, 14), // "test_triOrGate"
QT_MOC_LITERAL(11, 129, 15), // "test_triEorGate"
QT_MOC_LITERAL(12, 145, 13), // "test_nodeLink"
QT_MOC_LITERAL(13, 159, 12), // "test_circuit"
QT_MOC_LITERAL(14, 172, 14) // "test_save_load"

    },
    "Tests\0test_andGate\0\0test_orGate\0"
    "test_notGate\0test_eorGate\0test_xorGate\0"
    "test_norGate\0test_nandGate\0test_triAndGate\0"
    "test_triOrGate\0test_triEorGate\0"
    "test_nodeLink\0test_circuit\0test_save_load"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Tests[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x08 /* Private */,
       3,    0,   80,    2, 0x08 /* Private */,
       4,    0,   81,    2, 0x08 /* Private */,
       5,    0,   82,    2, 0x08 /* Private */,
       6,    0,   83,    2, 0x08 /* Private */,
       7,    0,   84,    2, 0x08 /* Private */,
       8,    0,   85,    2, 0x08 /* Private */,
       9,    0,   86,    2, 0x08 /* Private */,
      10,    0,   87,    2, 0x08 /* Private */,
      11,    0,   88,    2, 0x08 /* Private */,
      12,    0,   89,    2, 0x08 /* Private */,
      13,    0,   90,    2, 0x08 /* Private */,
      14,    0,   91,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Tests::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Tests *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->test_andGate(); break;
        case 1: _t->test_orGate(); break;
        case 2: _t->test_notGate(); break;
        case 3: _t->test_eorGate(); break;
        case 4: _t->test_xorGate(); break;
        case 5: _t->test_norGate(); break;
        case 6: _t->test_nandGate(); break;
        case 7: _t->test_triAndGate(); break;
        case 8: _t->test_triOrGate(); break;
        case 9: _t->test_triEorGate(); break;
        case 10: _t->test_nodeLink(); break;
        case 11: _t->test_circuit(); break;
        case 12: _t->test_save_load(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject Tests::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_Tests.data,
    qt_meta_data_Tests,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Tests::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Tests::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Tests.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Tests::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
