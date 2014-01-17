/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[23];
    char stringdata[328];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_MainWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 10),
QT_MOC_LITERAL(2, 22, 0),
QT_MOC_LITERAL(3, 23, 7),
QT_MOC_LITERAL(4, 31, 11),
QT_MOC_LITERAL(5, 43, 19),
QT_MOC_LITERAL(6, 63, 25),
QT_MOC_LITERAL(7, 89, 26),
QT_MOC_LITERAL(8, 116, 23),
QT_MOC_LITERAL(9, 140, 22),
QT_MOC_LITERAL(10, 163, 20),
QT_MOC_LITERAL(11, 184, 20),
QT_MOC_LITERAL(12, 205, 11),
QT_MOC_LITERAL(13, 217, 13),
QT_MOC_LITERAL(14, 231, 8),
QT_MOC_LITERAL(15, 240, 14),
QT_MOC_LITERAL(16, 255, 13),
QT_MOC_LITERAL(17, 269, 2),
QT_MOC_LITERAL(18, 272, 3),
QT_MOC_LITERAL(19, 276, 16),
QT_MOC_LITERAL(20, 293, 9),
QT_MOC_LITERAL(21, 303, 4),
QT_MOC_LITERAL(22, 308, 18)
    },
    "MainWindow\0readStdout\0\0startW3\0"
    "startUpdate\0updateCheckFinished\0"
    "on_pushButtonSWGP_clicked\0"
    "on_pushButtonSWOGP_clicked\0"
    "on_pushButtonBU_clicked\0on_closeButton_clicked\0"
    "on_maxButton_clicked\0on_minButton_clicked\0"
    "gproxyReady\0gproxyExiting\0w3Exited\0"
    "updateFinished\0restartNeeded\0ok\0utd\0"
    "hideSplashScreen\0logUpdate\0line\0"
    "modifyLastLineSlot\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   99,    2, 0x06,
       3,    0,  100,    2, 0x06,
       4,    0,  101,    2, 0x06,
       5,    0,  102,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
       6,    0,  103,    2, 0x08,
       7,    0,  104,    2, 0x08,
       8,    0,  105,    2, 0x08,
       9,    0,  106,    2, 0x08,
      10,    0,  107,    2, 0x08,
      11,    0,  108,    2, 0x08,
      12,    0,  109,    2, 0x0a,
      13,    0,  110,    2, 0x0a,
      14,    0,  111,    2, 0x0a,
      15,    3,  112,    2, 0x0a,
      19,    0,  119,    2, 0x0a,
      20,    1,  120,    2, 0x0a,
      22,    1,  123,    2, 0x0a,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

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
    QMetaType::Void, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool,   16,   17,   18,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   21,
    QMetaType::Void, QMetaType::QString,   21,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->readStdout(); break;
        case 1: _t->startW3(); break;
        case 2: _t->startUpdate(); break;
        case 3: _t->updateCheckFinished(); break;
        case 4: _t->on_pushButtonSWGP_clicked(); break;
        case 5: _t->on_pushButtonSWOGP_clicked(); break;
        case 6: _t->on_pushButtonBU_clicked(); break;
        case 7: _t->on_closeButton_clicked(); break;
        case 8: _t->on_maxButton_clicked(); break;
        case 9: _t->on_minButton_clicked(); break;
        case 10: _t->gproxyReady(); break;
        case 11: _t->gproxyExiting(); break;
        case 12: _t->w3Exited(); break;
        case 13: _t->updateFinished((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 14: _t->hideSplashScreen(); break;
        case 15: _t->logUpdate((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 16: _t->modifyLastLineSlot((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::readStdout)) {
                *result = 0;
            }
        }
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::startW3)) {
                *result = 1;
            }
        }
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::startUpdate)) {
                *result = 2;
            }
        }
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::updateCheckFinished)) {
                *result = 3;
            }
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, 0, 0}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::readStdout()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void MainWindow::startW3()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void MainWindow::startUpdate()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void MainWindow::updateCheckFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}
QT_END_MOC_NAMESPACE
