/****************************************************************************
** Meta object code from reading C++ file 'settingWindow.hpp'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../marketStalker/settingWindow.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'settingWindow.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_settingWindowClass[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      87,   20,   19,   19, 0x05,

 // slots: signature, parameters, type, tag, flags
     130,  121,   19,   19, 0x0a,
     150,   19,   19,   19, 0x0a,
     165,   19,   19,   19, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_settingWindowClass[] = {
    "settingWindowClass\0\0"
    "euroChange,emailIsActiveChange,smtpOrEmailToCoChange,englishChange\0"
    "updateOption(bool,bool,bool,bool)\0"
    "newValue\0boxHasChanged(bool)\0"
    "acceptOption()\0rejectOption()\0"
};

void settingWindowClass::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        settingWindowClass *_t = static_cast<settingWindowClass *>(_o);
        switch (_id) {
        case 0: _t->updateOption((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4]))); break;
        case 1: _t->boxHasChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->acceptOption(); break;
        case 3: _t->rejectOption(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData settingWindowClass::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject settingWindowClass::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_settingWindowClass,
      qt_meta_data_settingWindowClass, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &settingWindowClass::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *settingWindowClass::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *settingWindowClass::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_settingWindowClass))
        return static_cast<void*>(const_cast< settingWindowClass*>(this));
    return QDialog::qt_metacast(_clname);
}

int settingWindowClass::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void settingWindowClass::updateOption(bool _t1, bool _t2, bool _t3, bool _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
