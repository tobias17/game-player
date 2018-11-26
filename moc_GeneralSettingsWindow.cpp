/****************************************************************************
** Meta object code from reading C++ file 'GeneralSettingsWindow.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "GeneralSettingsWindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GeneralSettingsWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GeneralSettingsWindow[] = {

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
      23,   22,   22,   22, 0x05,

 // slots: signature, parameters, type, tag, flags
      53,   22,   22,   22, 0x0a,
      74,   22,   22,   22, 0x08,
      94,   22,   22,   22, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_GeneralSettingsWindow[] = {
    "GeneralSettingsWindow\0\0"
    "sendSettings(vector<QString>)\0"
    "receiveCloseWindow()\0saveButtonHandler()\0"
    "closeButtonHandler()\0"
};

void GeneralSettingsWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GeneralSettingsWindow *_t = static_cast<GeneralSettingsWindow *>(_o);
        switch (_id) {
        case 0: _t->sendSettings((*reinterpret_cast< vector<QString>(*)>(_a[1]))); break;
        case 1: _t->receiveCloseWindow(); break;
        case 2: _t->saveButtonHandler(); break;
        case 3: _t->closeButtonHandler(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData GeneralSettingsWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject GeneralSettingsWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_GeneralSettingsWindow,
      qt_meta_data_GeneralSettingsWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GeneralSettingsWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GeneralSettingsWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GeneralSettingsWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GeneralSettingsWindow))
        return static_cast<void*>(const_cast< GeneralSettingsWindow*>(this));
    return QWidget::qt_metacast(_clname);
}

int GeneralSettingsWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
void GeneralSettingsWindow::sendSettings(vector<QString> _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
