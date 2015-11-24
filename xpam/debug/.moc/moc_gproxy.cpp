/****************************************************************************
** Meta object code from reading C++ file 'gproxy.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../gproxy.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gproxy.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_GProxy_t {
    QByteArrayData data[7];
    char stringdata[60];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_GProxy_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_GProxy_t qt_meta_stringdata_GProxy = {
    {
QT_MOC_LITERAL(0, 0, 6),
QT_MOC_LITERAL(1, 7, 8),
QT_MOC_LITERAL(2, 16, 0),
QT_MOC_LITERAL(3, 17, 4),
QT_MOC_LITERAL(4, 22, 11),
QT_MOC_LITERAL(5, 34, 13),
QT_MOC_LITERAL(6, 48, 10)
    },
    "GProxy\0sendLine\0\0line\0gproxyReady\0"
    "gproxyExiting\0readStdout\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GProxy[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06,
       4,    0,   37,    2, 0x06,
       5,    0,   38,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
       6,    0,   39,    2, 0x0a,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void GProxy::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GProxy *_t = static_cast<GProxy *>(_o);
        switch (_id) {
        case 0: _t->sendLine((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->gproxyReady(); break;
        case 2: _t->gproxyExiting(); break;
        case 3: _t->readStdout(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (GProxy::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GProxy::sendLine)) {
                *result = 0;
            }
        }
        {
            typedef void (GProxy::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GProxy::gproxyReady)) {
                *result = 1;
            }
        }
        {
            typedef void (GProxy::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GProxy::gproxyExiting)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject GProxy::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_GProxy.data,
      qt_meta_data_GProxy,  qt_static_metacall, 0, 0}
};


const QMetaObject *GProxy::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GProxy::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GProxy.stringdata))
        return static_cast<void*>(const_cast< GProxy*>(this));
    return QObject::qt_metacast(_clname);
}

int GProxy::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void GProxy::sendLine(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GProxy::gproxyReady()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void GProxy::gproxyExiting()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE
