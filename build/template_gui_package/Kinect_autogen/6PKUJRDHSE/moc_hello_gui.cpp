/****************************************************************************
** Meta object code from reading C++ file 'hello_gui.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "include/template_gui_package/hello_gui.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'hello_gui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_helloGui_t {
    QByteArrayData data[16];
    char stringdata0[205];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_helloGui_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_helloGui_t qt_meta_stringdata_helloGui = {
    {
QT_MOC_LITERAL(0, 0, 8), // "helloGui"
QT_MOC_LITERAL(1, 9, 8), // "spinOnce"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 4), // "spin"
QT_MOC_LITERAL(4, 24, 16), // "openSecondWindow"
QT_MOC_LITERAL(5, 41, 8), // "openwin3"
QT_MOC_LITERAL(6, 50, 8), // "openwin4"
QT_MOC_LITERAL(7, 59, 11), // "receiveData"
QT_MOC_LITERAL(8, 71, 4), // "data"
QT_MOC_LITERAL(9, 76, 8), // "not_hide"
QT_MOC_LITERAL(10, 85, 1), // "f"
QT_MOC_LITERAL(11, 87, 23), // "on_pushButton_7_clicked"
QT_MOC_LITERAL(12, 111, 23), // "on_pushButton_8_clicked"
QT_MOC_LITERAL(13, 135, 23), // "on_pushButton_9_clicked"
QT_MOC_LITERAL(14, 159, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(15, 181, 23) // "on_pushButton_2_pressed"

    },
    "helloGui\0spinOnce\0\0spin\0openSecondWindow\0"
    "openwin3\0openwin4\0receiveData\0data\0"
    "not_hide\0f\0on_pushButton_7_clicked\0"
    "on_pushButton_8_clicked\0on_pushButton_9_clicked\0"
    "on_pushButton_clicked\0on_pushButton_2_pressed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_helloGui[] = {

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
       1,    0,   74,    2, 0x0a /* Public */,
       3,    0,   75,    2, 0x0a /* Public */,
       4,    0,   76,    2, 0x0a /* Public */,
       5,    0,   77,    2, 0x0a /* Public */,
       6,    0,   78,    2, 0x0a /* Public */,
       7,    1,   79,    2, 0x0a /* Public */,
       9,    1,   82,    2, 0x0a /* Public */,
      11,    0,   85,    2, 0x08 /* Private */,
      12,    0,   86,    2, 0x08 /* Private */,
      13,    0,   87,    2, 0x08 /* Private */,
      14,    0,   88,    2, 0x08 /* Private */,
      15,    0,   89,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Bool,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void helloGui::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<helloGui *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->spinOnce(); break;
        case 1: _t->spin(); break;
        case 2: _t->openSecondWindow(); break;
        case 3: _t->openwin3(); break;
        case 4: _t->openwin4(); break;
        case 5: _t->receiveData((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->not_hide((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->on_pushButton_7_clicked(); break;
        case 8: _t->on_pushButton_8_clicked(); break;
        case 9: _t->on_pushButton_9_clicked(); break;
        case 10: _t->on_pushButton_clicked(); break;
        case 11: _t->on_pushButton_2_pressed(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject helloGui::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_helloGui.data,
    qt_meta_data_helloGui,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *helloGui::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *helloGui::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_helloGui.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int helloGui::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
