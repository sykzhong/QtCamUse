/****************************************************************************
** Meta object code from reading C++ file 'QtCamUse_move.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../QtCamUse_move.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QtCamUse_move.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QtCamUse_move_t {
    QByteArrayData data[13];
    char stringdata0[315];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QtCamUse_move_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QtCamUse_move_t qt_meta_stringdata_QtCamUse_move = {
    {
QT_MOC_LITERAL(0, 0, 13), // "QtCamUse_move"
QT_MOC_LITERAL(1, 14, 18), // "back_to_mainwindow"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 18), // "get_template_image"
QT_MOC_LITERAL(4, 53, 14), // "get_back_image"
QT_MOC_LITERAL(5, 68, 13), // "Image_process"
QT_MOC_LITERAL(6, 82, 3), // "img"
QT_MOC_LITERAL(7, 86, 40), // "on_pushButton_back_to_mainwin..."
QT_MOC_LITERAL(8, 127, 35), // "on_pushButton_get_back_save_c..."
QT_MOC_LITERAL(9, 163, 35), // "on_pushButton_get_back_load_c..."
QT_MOC_LITERAL(10, 199, 39), // "on_pushButton_get_template_sa..."
QT_MOC_LITERAL(11, 239, 39), // "on_pushButton_get_template_lo..."
QT_MOC_LITERAL(12, 279, 35) // "on_pushButton_image_process_c..."

    },
    "QtCamUse_move\0back_to_mainwindow\0\0"
    "get_template_image\0get_back_image\0"
    "Image_process\0img\0"
    "on_pushButton_back_to_mainwindow_clicked\0"
    "on_pushButton_get_back_save_clicked\0"
    "on_pushButton_get_back_load_clicked\0"
    "on_pushButton_get_template_save_clicked\0"
    "on_pushButton_get_template_load_clicked\0"
    "on_pushButton_image_process_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QtCamUse_move[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x06 /* Public */,
       3,    0,   65,    2, 0x06 /* Public */,
       4,    0,   66,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   67,    2, 0x08 /* Private */,
       7,    0,   70,    2, 0x08 /* Private */,
       8,    0,   71,    2, 0x08 /* Private */,
       9,    0,   72,    2, 0x08 /* Private */,
      10,    0,   73,    2, 0x08 /* Private */,
      11,    0,   74,    2, 0x08 /* Private */,
      12,    0,   75,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QImage,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void QtCamUse_move::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QtCamUse_move *_t = static_cast<QtCamUse_move *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->back_to_mainwindow(); break;
        case 1: _t->get_template_image(); break;
        case 2: _t->get_back_image(); break;
        case 3: _t->Image_process((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 4: _t->on_pushButton_back_to_mainwindow_clicked(); break;
        case 5: _t->on_pushButton_get_back_save_clicked(); break;
        case 6: _t->on_pushButton_get_back_load_clicked(); break;
        case 7: _t->on_pushButton_get_template_save_clicked(); break;
        case 8: _t->on_pushButton_get_template_load_clicked(); break;
        case 9: _t->on_pushButton_image_process_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (QtCamUse_move::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QtCamUse_move::back_to_mainwindow)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (QtCamUse_move::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QtCamUse_move::get_template_image)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (QtCamUse_move::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QtCamUse_move::get_back_image)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject QtCamUse_move::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_QtCamUse_move.data,
      qt_meta_data_QtCamUse_move,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *QtCamUse_move::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QtCamUse_move::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_QtCamUse_move.stringdata0))
        return static_cast<void*>(const_cast< QtCamUse_move*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int QtCamUse_move::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void QtCamUse_move::back_to_mainwindow()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void QtCamUse_move::get_template_image()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void QtCamUse_move::get_back_image()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
