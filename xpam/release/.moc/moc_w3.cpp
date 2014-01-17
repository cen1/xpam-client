/****************************************************************************
** Meta object code from reading C++ file 'w3.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../w3.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'w3.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_W3_t {
    QByteArrayData data[4];
    char stringdata[22];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_W3_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_W3_t qt_meta_stringdata_W3 = {
    {
QT_MOC_LITERAL(0, 0, 2),
QT_MOC_LITERAL(1, 3, 8),
QT_MOC_LITERAL(2, 12, 0),
QT_MOC_LITERAL(3, 13, 7)
    },
    "W3\0w3Exited\0\0startW3\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_W3[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
       3,    0,   25,    2, 0x0a,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void W3::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        W3 *_t = static_cast<W3 *>(_o);
        switch (_id) {
        case 0: _t->w3Exited(); break;
        case 1: _t->startW3(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (W3::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&W3::w3Exited)) {
                *result = 0;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject W3::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_W3.data,
      qt_meta_data_W3,  qt_static_metacall, 0, 0}
};


const QMetaObject *W3::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *W3::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_W3.stringdata))
        return static_cast<void*>(const_cast< W3*>(this));
    return QObject::qt_metacast(_clname);
}

int W3::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void W3::w3Exited()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
