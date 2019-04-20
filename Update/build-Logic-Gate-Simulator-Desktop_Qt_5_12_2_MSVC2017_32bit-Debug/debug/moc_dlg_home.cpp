/****************************************************************************
** Meta object code from reading C++ file 'dlg_home.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Logic_Gate_Simulator/dlg_home.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dlg_home.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DLG_Home_t {
    QByteArrayData data[15];
    char stringdata0[301];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DLG_Home_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DLG_Home_t qt_meta_stringdata_DLG_Home = {
    {
QT_MOC_LITERAL(0, 0, 8), // "DLG_Home"
QT_MOC_LITERAL(1, 9, 19), // "on_btn_Drag_clicked"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 21), // "on_btn_Delete_clicked"
QT_MOC_LITERAL(4, 52, 19), // "on_btn_link_clicked"
QT_MOC_LITERAL(5, 72, 22), // "on_btn_newPage_clicked"
QT_MOC_LITERAL(6, 95, 25), // "on_btn_sourceGate_clicked"
QT_MOC_LITERAL(7, 121, 22), // "on_btn_notGate_clicked"
QT_MOC_LITERAL(8, 144, 21), // "on_btn_orGate_clicked"
QT_MOC_LITERAL(9, 166, 22), // "on_btn_andGate_clicked"
QT_MOC_LITERAL(10, 189, 30), // "on_PlayField_tabCloseRequested"
QT_MOC_LITERAL(11, 220, 5), // "index"
QT_MOC_LITERAL(12, 226, 27), // "on_PlayField_currentChanged"
QT_MOC_LITERAL(13, 254, 25), // "on_btn_DeleteLink_clicked"
QT_MOC_LITERAL(14, 280, 20) // "on_btn_click_clicked"

    },
    "DLG_Home\0on_btn_Drag_clicked\0\0"
    "on_btn_Delete_clicked\0on_btn_link_clicked\0"
    "on_btn_newPage_clicked\0on_btn_sourceGate_clicked\0"
    "on_btn_notGate_clicked\0on_btn_orGate_clicked\0"
    "on_btn_andGate_clicked\0"
    "on_PlayField_tabCloseRequested\0index\0"
    "on_PlayField_currentChanged\0"
    "on_btn_DeleteLink_clicked\0"
    "on_btn_click_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DLG_Home[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x08 /* Private */,
       3,    0,   75,    2, 0x08 /* Private */,
       4,    0,   76,    2, 0x08 /* Private */,
       5,    0,   77,    2, 0x08 /* Private */,
       6,    0,   78,    2, 0x08 /* Private */,
       7,    0,   79,    2, 0x08 /* Private */,
       8,    0,   80,    2, 0x08 /* Private */,
       9,    0,   81,    2, 0x08 /* Private */,
      10,    1,   82,    2, 0x08 /* Private */,
      12,    1,   85,    2, 0x08 /* Private */,
      13,    0,   88,    2, 0x08 /* Private */,
      14,    0,   89,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void DLG_Home::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DLG_Home *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_btn_Drag_clicked(); break;
        case 1: _t->on_btn_Delete_clicked(); break;
        case 2: _t->on_btn_link_clicked(); break;
        case 3: _t->on_btn_newPage_clicked(); break;
        case 4: _t->on_btn_sourceGate_clicked(); break;
        case 5: _t->on_btn_notGate_clicked(); break;
        case 6: _t->on_btn_orGate_clicked(); break;
        case 7: _t->on_btn_andGate_clicked(); break;
        case 8: _t->on_PlayField_tabCloseRequested((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->on_PlayField_currentChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->on_btn_DeleteLink_clicked(); break;
        case 11: _t->on_btn_click_clicked(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject DLG_Home::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_DLG_Home.data,
    qt_meta_data_DLG_Home,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DLG_Home::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DLG_Home::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DLG_Home.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int DLG_Home::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
struct qt_meta_stringdata_LogicUpdateThread_t {
    QByteArrayData data[1];
    char stringdata0[18];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LogicUpdateThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LogicUpdateThread_t qt_meta_stringdata_LogicUpdateThread = {
    {
QT_MOC_LITERAL(0, 0, 17) // "LogicUpdateThread"

    },
    "LogicUpdateThread"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LogicUpdateThread[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void LogicUpdateThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject LogicUpdateThread::staticMetaObject = { {
    &QThread::staticMetaObject,
    qt_meta_stringdata_LogicUpdateThread.data,
    qt_meta_data_LogicUpdateThread,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *LogicUpdateThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LogicUpdateThread::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_LogicUpdateThread.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int LogicUpdateThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
