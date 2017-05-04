/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[19];
    char stringdata0[484];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 13), // "Image_process"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 3), // "img"
QT_MOC_LITERAL(4, 30, 14), // "camera_statues"
QT_MOC_LITERAL(5, 45, 27), // "slot_res_combobox_activated"
QT_MOC_LITERAL(6, 73, 5), // "index"
QT_MOC_LITERAL(7, 79, 32), // "slot_radioButton_collect_clicked"
QT_MOC_LITERAL(8, 112, 7), // "checked"
QT_MOC_LITERAL(9, 120, 41), // "slot_radioButton_software_tri..."
QT_MOC_LITERAL(10, 162, 41), // "slot_radioButton_hardware_tri..."
QT_MOC_LITERAL(11, 204, 41), // "slot_software_trigger_once_bu..."
QT_MOC_LITERAL(12, 246, 31), // "slot_exposure_mode_auto_clicked"
QT_MOC_LITERAL(13, 278, 33), // "slot_exposure_mode_manual_cli..."
QT_MOC_LITERAL(14, 312, 39), // "slot_horizontalSlider_gain_va..."
QT_MOC_LITERAL(15, 352, 48), // "slot_horizontalSlider_exposur..."
QT_MOC_LITERAL(16, 401, 30), // "on_pushButton_AWB_once_clicked"
QT_MOC_LITERAL(17, 432, 25), // "on_checkBox_isp_h_clicked"
QT_MOC_LITERAL(18, 458, 25) // "on_checkBox_isp_v_clicked"

    },
    "MainWindow\0Image_process\0\0img\0"
    "camera_statues\0slot_res_combobox_activated\0"
    "index\0slot_radioButton_collect_clicked\0"
    "checked\0slot_radioButton_software_trigger_clicked\0"
    "slot_radioButton_hardware_trigger_clicked\0"
    "slot_software_trigger_once_button_clicked\0"
    "slot_exposure_mode_auto_clicked\0"
    "slot_exposure_mode_manual_clicked\0"
    "slot_horizontalSlider_gain_valueChanged\0"
    "slot_horizontalSlider_exposure_time_valueChanged\0"
    "on_pushButton_AWB_once_clicked\0"
    "on_checkBox_isp_h_clicked\0"
    "on_checkBox_isp_v_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   84,    2, 0x08 /* Private */,
       4,    0,   87,    2, 0x08 /* Private */,
       5,    1,   88,    2, 0x08 /* Private */,
       7,    1,   91,    2, 0x08 /* Private */,
       9,    1,   94,    2, 0x08 /* Private */,
      10,    1,   97,    2, 0x08 /* Private */,
      11,    0,  100,    2, 0x08 /* Private */,
      12,    1,  101,    2, 0x08 /* Private */,
      13,    1,  104,    2, 0x08 /* Private */,
      14,    1,  107,    2, 0x08 /* Private */,
      15,    1,  110,    2, 0x08 /* Private */,
      16,    0,  113,    2, 0x08 /* Private */,
      17,    1,  114,    2, 0x08 /* Private */,
      18,    1,  117,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QImage,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Bool,    8,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    8,
    QMetaType::Void, QMetaType::Bool,    8,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Image_process((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 1: _t->camera_statues(); break;
        case 2: _t->slot_res_combobox_activated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->slot_radioButton_collect_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->slot_radioButton_software_trigger_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->slot_radioButton_hardware_trigger_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->slot_software_trigger_once_button_clicked(); break;
        case 7: _t->slot_exposure_mode_auto_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->slot_exposure_mode_manual_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->slot_horizontalSlider_gain_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->slot_horizontalSlider_exposure_time_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->on_pushButton_AWB_once_clicked(); break;
        case 12: _t->on_checkBox_isp_h_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 13: _t->on_checkBox_isp_v_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
