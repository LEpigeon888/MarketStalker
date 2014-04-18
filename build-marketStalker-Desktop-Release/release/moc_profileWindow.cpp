/****************************************************************************
** Meta object code from reading C++ file 'profileWindow.hpp'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../marketStalker/profileWindow.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'profileWindow.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_profileWindowClass[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x05,

 // slots: signature, parameters, type, tag, flags
      33,   19,   19,   19, 0x0a,
      47,   19,   19,   19, 0x0a,
      63,   19,   19,   19, 0x0a,
      79,   19,   19,   19, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_profileWindowClass[] = {
    "profileWindowClass\0\0allChanged()\0"
    "saveProfile()\0addNewProfile()\0"
    "deleteProfile()\0selectProfile()\0"
};

void profileWindowClass::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        profileWindowClass *_t = static_cast<profileWindowClass *>(_o);
        switch (_id) {
        case 0: _t->allChanged(); break;
        case 1: _t->saveProfile(); break;
        case 2: _t->addNewProfile(); break;
        case 3: _t->deleteProfile(); break;
        case 4: _t->selectProfile(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData profileWindowClass::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject profileWindowClass::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_profileWindowClass,
      qt_meta_data_profileWindowClass, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &profileWindowClass::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *profileWindowClass::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *profileWindowClass::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_profileWindowClass))
        return static_cast<void*>(const_cast< profileWindowClass*>(this));
    return QDialog::qt_metacast(_clname);
}

int profileWindowClass::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void profileWindowClass::allChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
