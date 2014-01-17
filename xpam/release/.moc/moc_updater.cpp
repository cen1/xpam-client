/****************************************************************************
** Meta object code from reading C++ file 'updater.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../updater.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'updater.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Updater_t {
    QByteArrayData data[17];
    char stringdata[174];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_Updater_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_Updater_t qt_meta_stringdata_Updater = {
    {
QT_MOC_LITERAL(0, 0, 7),
QT_MOC_LITERAL(1, 8, 14),
QT_MOC_LITERAL(2, 23, 0),
QT_MOC_LITERAL(3, 24, 13),
QT_MOC_LITERAL(4, 38, 2),
QT_MOC_LITERAL(5, 41, 3),
QT_MOC_LITERAL(6, 45, 8),
QT_MOC_LITERAL(7, 54, 4),
QT_MOC_LITERAL(8, 59, 14),
QT_MOC_LITERAL(9, 74, 7),
QT_MOC_LITERAL(10, 82, 16),
QT_MOC_LITERAL(11, 99, 11),
QT_MOC_LITERAL(12, 111, 15),
QT_MOC_LITERAL(13, 127, 13),
QT_MOC_LITERAL(14, 141, 10),
QT_MOC_LITERAL(15, 152, 15),
QT_MOC_LITERAL(16, 168, 4)
    },
    "Updater\0updateFinished\0\0restartNeeded\0"
    "ok\0utd\0sendLine\0line\0modifyLastLine\0"
    "startDl\0hideSplashScreen\0startUpdate\0"
    "receiveProgress\0bytesReceived\0bytesTotal\0"
    "receiveFinishdl\0data\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Updater[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   54,    2, 0x06,
       6,    1,   61,    2, 0x06,
       8,    1,   64,    2, 0x06,
       9,    0,   67,    2, 0x06,
      10,    0,   68,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
      11,    0,   69,    2, 0x0a,
      12,    2,   70,    2, 0x0a,
      15,    1,   75,    2, 0x0a,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool,    3,    4,    5,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong,   13,   14,
    QMetaType::Void, QMetaType::QByteArray,   16,

       0        // eod
};

void Updater::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Updater *_t = static_cast<Updater *>(_o);
        switch (_id) {
        case 0: _t->updateFinished((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 1: _t->sendLine((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->modifyLastLine((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->startDl(); break;
        case 4: _t->hideSplashScreen(); break;
        case 5: _t->startUpdate(); break;
        case 6: _t->receiveProgress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 7: _t->receiveFinishdl((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Updater::*_t)(bool , bool , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Updater::updateFinished)) {
                *result = 0;
            }
        }
        {
            typedef void (Updater::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Updater::sendLine)) {
                *result = 1;
            }
        }
        {
            typedef void (Updater::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Updater::modifyLastLine)) {
                *result = 2;
            }
        }
        {
            typedef void (Updater::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Updater::startDl)) {
                *result = 3;
            }
        }
        {
            typedef void (Updater::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Updater::hideSplashScreen)) {
                *result = 4;
            }
        }
    }
}

const QMetaObject Updater::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Updater.data,
      qt_meta_data_Updater,  qt_static_metacall, 0, 0}
};


const QMetaObject *Updater::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Updater::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Updater.stringdata))
        return static_cast<void*>(const_cast< Updater*>(this));
    return QObject::qt_metacast(_clname);
}

int Updater::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void Updater::updateFinished(bool _t1, bool _t2, bool _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Updater::sendLine(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Updater::modifyLastLine(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Updater::startDl()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void Updater::hideSplashScreen()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}
QT_END_MOC_NAMESPACE
