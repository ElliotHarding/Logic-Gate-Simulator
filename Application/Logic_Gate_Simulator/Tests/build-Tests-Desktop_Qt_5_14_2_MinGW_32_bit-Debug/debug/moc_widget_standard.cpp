/****************************************************************************
** Meta object code from reading C++ file 'widget_standard.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../Dialogs/widget_standard.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'widget_standard.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Widget_Standard_t {
    QByteArrayData data[9];
    char stringdata0[185];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Widget_Standard_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Widget_Standard_t qt_meta_stringdata_Widget_Standard = {
    {
QT_MOC_LITERAL(0, 0, 15), // "Widget_Standard"
QT_MOC_LITERAL(1, 16, 21), // "on_btn_orGate_clicked"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 22), // "on_btn_notGate_clicked"
QT_MOC_LITERAL(4, 62, 22), // "on_btn_andGate_clicked"
QT_MOC_LITERAL(5, 85, 24), // "on_btn_GateTriOr_clicked"
QT_MOC_LITERAL(6, 110, 25), // "on_btn_GateTriAnd_clicked"
QT_MOC_LITERAL(7, 136, 22), // "on_btn_GateEor_clicked"
QT_MOC_LITERAL(8, 159, 25) // "on_btn_GateTriEor_clicked"

    },
    "Widget_Standard\0on_btn_orGate_clicked\0"
    "\0on_btn_notGate_clicked\0on_btn_andGate_clicked\0"
    "on_btn_GateTriOr_clicked\0"
    "on_btn_GateTriAnd_clicked\0"
    "on_btn_GateEor_clicked\0on_btn_GateTriEor_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Widget_Standard[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x08 /* Private */,
       3,    0,   50,    2, 0x08 /* Private */,
       4,    0,   51,    2, 0x08 /* Private */,
       5,    0,   52,    2, 0x08 /* Private */,
       6,    0,   53,    2, 0x08 /* Private */,
       7,    0,   54,    2, 0x08 /* Private */,
       8,    0,   55,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Widget_Standard::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Widget_Standard *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_btn_orGate_clicked(); break;
        case 1: _t->on_btn_notGate_clicked(); break;
        case 2: _t->on_btn_andGate_clicked(); break;
        case 3: _t->on_btn_GateTriOr_clicked(); break;
        case 4: _t->on_btn_GateTriAnd_clicked(); break;
        case 5: _t->on_btn_GateEor_clicked(); break;
        case 6: _t->on_btn_GateTriEor_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject Widget_Standard::staticMetaObject = { {
    QMetaObject::SuperData::link<MovingWidget::staticMetaObject>(),
    qt_meta_stringdata_Widget_Standard.data,
    qt_meta_data_Widget_Standard,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Widget_Standard::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Widget_Standard::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Widget_Standard.stringdata0))
        return static_cast<void*>(this);
    return MovingWidget::qt_metacast(_clname);
}

int Widget_Standard::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = MovingWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
