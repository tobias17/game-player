/****************************************************************************
** Meta object code from reading C++ file 'TicTacToeSettings.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "NPlayerTTTSettings.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TicTacToeSettings.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TicTacToeSettingsWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      25,   24,   24,   24, 0x05,

 // slots: signature, parameters, type, tag, flags
      68,   24,   24,   24, 0x08,
      88,   24,   24,   24, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_TicTacToeSettingsWindow[] = {
    "TicTacToeSettingsWindow\0\0"
    "sendTicTacToeSettings(TicTacToeSettings_t)\0"
    "saveButtonHandler()\0closeButtonHandler()\0"
};

void TicTacToeSettingsWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        TicTacToeSettingsWindow *_t = static_cast<TicTacToeSettingsWindow *>(_o);
        switch (_id) {
        case 0: _t->sendTicTacToeSettings((*reinterpret_cast< TicTacToeSettings_t(*)>(_a[1]))); break;
        case 1: _t->saveButtonHandler(); break;
        case 2: _t->closeButtonHandler(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData TicTacToeSettingsWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject TicTacToeSettingsWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_TicTacToeSettingsWindow,
      qt_meta_data_TicTacToeSettingsWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TicTacToeSettingsWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TicTacToeSettingsWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TicTacToeSettingsWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TicTacToeSettingsWindow))
        return static_cast<void*>(const_cast< TicTacToeSettingsWindow*>(this));
    return QWidget::qt_metacast(_clname);
}

int TicTacToeSettingsWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void TicTacToeSettingsWindow::sendTicTacToeSettings(TicTacToeSettings_t _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE