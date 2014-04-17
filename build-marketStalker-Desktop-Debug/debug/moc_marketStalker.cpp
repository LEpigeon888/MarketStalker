/****************************************************************************
** Meta object code from reading C++ file 'marketStalker.hpp'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../marketStalker/marketStalker.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'marketStalker.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_marketStalkerClass[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      28,   20,   19,   19, 0x05,
      55,   19,   19,   19, 0x05,

 // slots: signature, parameters, type, tag, flags
      69,   19,   19,   19, 0x0a,
      87,   19,   19,   19, 0x0a,
     101,   19,   19,   19, 0x0a,
     116,   19,   19,   19, 0x0a,
     139,  130,   19,   19, 0x0a,
     175,  166,   19,   19, 0x0a,
     201,   19,   19,   19, 0x0a,
     214,   19,   19,   19, 0x0a,
     225,   19,   19,   19, 0x0a,
     306,  239,   19,   19, 0x0a,
     340,  130,   19,   19, 0x0a,
     380,  368,   19,   19, 0x0a,
     410,   19,   19,   19, 0x0a,
     426,   19,   19,   19, 0x0a,
     454,  444,   19,   19, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_marketStalkerClass[] = {
    "marketStalkerClass\0\0newName\0"
    "windowNameChanged(QString)\0logsChanged()\0"
    "checkPageEndUse()\0updateValue()\0"
    "startGetPage()\0beginAllGet()\0thisPage\0"
    "thisGetEnd(getAPageClass*)\0thisItem\0"
    "goToUrl(QTreeWidgetItem*)\0showOption()\0"
    "showLogs()\0showProfile()\0"
    "euroChange,emailIsActiveChange,smtpOrEmailToCoChange,englishChange\0"
    "updateOption(bool,bool,bool,bool)\0"
    "errorDelete(getAPageClass*)\0old,current\0"
    "checkFocus(QWidget*,QWidget*)\0"
    "itsTimeToWarn()\0updateAllOption()\0"
    "thisPoint\0creatContextMenu(QPoint)\0"
};

void marketStalkerClass::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        marketStalkerClass *_t = static_cast<marketStalkerClass *>(_o);
        switch (_id) {
        case 0: _t->windowNameChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->logsChanged(); break;
        case 2: _t->checkPageEndUse(); break;
        case 3: _t->updateValue(); break;
        case 4: _t->startGetPage(); break;
        case 5: _t->beginAllGet(); break;
        case 6: _t->thisGetEnd((*reinterpret_cast< getAPageClass*(*)>(_a[1]))); break;
        case 7: _t->goToUrl((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1]))); break;
        case 8: _t->showOption(); break;
        case 9: _t->showLogs(); break;
        case 10: _t->showProfile(); break;
        case 11: _t->updateOption((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4]))); break;
        case 12: _t->errorDelete((*reinterpret_cast< getAPageClass*(*)>(_a[1]))); break;
        case 13: _t->checkFocus((*reinterpret_cast< QWidget*(*)>(_a[1])),(*reinterpret_cast< QWidget*(*)>(_a[2]))); break;
        case 14: _t->itsTimeToWarn(); break;
        case 15: _t->updateAllOption(); break;
        case 16: _t->creatContextMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData marketStalkerClass::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject marketStalkerClass::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_marketStalkerClass,
      qt_meta_data_marketStalkerClass, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &marketStalkerClass::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *marketStalkerClass::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *marketStalkerClass::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_marketStalkerClass))
        return static_cast<void*>(const_cast< marketStalkerClass*>(this));
    return QWidget::qt_metacast(_clname);
}

int marketStalkerClass::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void marketStalkerClass::windowNameChanged(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void marketStalkerClass::logsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
