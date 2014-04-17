/****************************************************************************
** Meta object code from reading C++ file 'email.hpp'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../marketStalker/email.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'email.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_emailClass[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      23,   12,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      51,   39,   11,   11, 0x08,
     106,   94,   11,   11, 0x08,
     150,   11,   11,   11, 0x08,
     173,   11,   11,   11, 0x08,
     185,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_emailClass[] = {
    "emailClass\0\0thisStatus\0status(QString)\0"
    "socketState\0stateChanged(QAbstractSocket::SocketState)\0"
    "socketError\0errorReceived(QAbstractSocket::SocketError)\0"
    "disconnectedFromHost()\0connected()\0"
    "readyRead()\0"
};

void emailClass::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        emailClass *_t = static_cast<emailClass *>(_o);
        switch (_id) {
        case 0: _t->status((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->stateChanged((*reinterpret_cast< QAbstractSocket::SocketState(*)>(_a[1]))); break;
        case 2: _t->errorReceived((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 3: _t->disconnectedFromHost(); break;
        case 4: _t->connected(); break;
        case 5: _t->readyRead(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData emailClass::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject emailClass::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_emailClass,
      qt_meta_data_emailClass, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &emailClass::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *emailClass::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *emailClass::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_emailClass))
        return static_cast<void*>(const_cast< emailClass*>(this));
    return QObject::qt_metacast(_clname);
}

int emailClass::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void emailClass::status(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
