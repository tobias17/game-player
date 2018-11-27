/****************************************************************************
** Meta object code from reading C++ file 'Connect4Settings.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Connect4Settings.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Connect4Settings.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Connect4SettingsController[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      28,   27,   27,   27, 0x05,

 // slots: signature, parameters, type, tag, flags
      46,   27,   27,   27, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Connect4SettingsController[] = {
    "Connect4SettingsController\0\0"
    "sendCloseWindow()\0receiveSettings(vector<QString>)\0"
};

void Connect4SettingsController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Connect4SettingsController *_t = static_cast<Connect4SettingsController *>(_o);
        switch (_id) {
        case 0: _t->sendCloseWindow(); break;
        case 1: _t->receiveSettings((*reinterpret_cast< vector<QString>(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Connect4SettingsController::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Connect4SettingsController::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Connect4SettingsController,
      qt_meta_data_Connect4SettingsController, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Connect4SettingsController::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Connect4SettingsController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Connect4SettingsController::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Connect4SettingsController))
        return static_cast<void*>(const_cast< Connect4SettingsController*>(this));
    return QObject::qt_metacast(_clname);
}

int Connect4SettingsController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void Connect4SettingsController::sendCloseWindow()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
