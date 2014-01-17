/****************************************************************************
** Meta object code from reading C++ file 'downloader.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../downloader.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'downloader.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Downloader_t {
    QByteArrayData data[15];
    char stringdata[154];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_Downloader_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_Downloader_t qt_meta_stringdata_Downloader = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 8),
QT_MOC_LITERAL(2, 20, 0),
QT_MOC_LITERAL(3, 21, 13),
QT_MOC_LITERAL(4, 35, 10),
QT_MOC_LITERAL(5, 46, 10),
QT_MOC_LITERAL(6, 57, 4),
QT_MOC_LITERAL(7, 62, 8),
QT_MOC_LITERAL(8, 71, 4),
QT_MOC_LITERAL(9, 76, 12),
QT_MOC_LITERAL(10, 89, 12),
QT_MOC_LITERAL(11, 102, 9),
QT_MOC_LITERAL(12, 112, 27),
QT_MOC_LITERAL(13, 140, 4),
QT_MOC_LITERAL(14, 145, 7)
    },
    "Downloader\0progress\0\0bytesReceived\0"
    "bytesTotal\0finisheddl\0data\0sendInfo\0"
    "info\0progressSlot\0finishedSlot\0errorSlot\0"
    "QNetworkReply::NetworkError\0code\0"
    "startDl\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Downloader[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   49,    2, 0x06,
       5,    1,   54,    2, 0x06,
       7,    1,   57,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
       9,    2,   60,    2, 0x0a,
      10,    0,   65,    2, 0x0a,
      11,    1,   66,    2, 0x0a,
      14,    0,   69,    2, 0x0a,

 // signals: parameters
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong,    3,    4,
    QMetaType::Void, QMetaType::QByteArray,    6,
    QMetaType::Void, QMetaType::QString,    8,

 // slots: parameters
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong,    3,    4,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void,

       0        // eod
};

void Downloader::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Downloader *_t = static_cast<Downloader *>(_o);
        switch (_id) {
        case 0: _t->progress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 1: _t->finisheddl((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 2: _t->sendInfo((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->progressSlot((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 4: _t->finishedSlot(); break;
        case 5: _t->errorSlot((*reinterpret_cast< QNetworkReply::NetworkError(*)>(_a[1]))); break;
        case 6: _t->startDl(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply::NetworkError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Downloader::*_t)(qint64 , qint64 );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Downloader::progress)) {
                *result = 0;
            }
        }
        {
            typedef void (Downloader::*_t)(QByteArray );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Downloader::finisheddl)) {
                *result = 1;
            }
        }
        {
            typedef void (Downloader::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Downloader::sendInfo)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject Downloader::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Downloader.data,
      qt_meta_data_Downloader,  qt_static_metacall, 0, 0}
};


const QMetaObject *Downloader::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Downloader::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Downloader.stringdata))
        return static_cast<void*>(const_cast< Downloader*>(this));
    return QObject::qt_metacast(_clname);
}

int Downloader::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void Downloader::progress(qint64 _t1, qint64 _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Downloader::finisheddl(QByteArray _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Downloader::sendInfo(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
