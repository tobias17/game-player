/****************************************************************************
** Meta object code from reading C++ file 'TicTacToeGameWindow.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "TicTacToeGameWindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TicTacToeGameWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TicTacToeGameWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      21,   20,   20,   20, 0x05,
      39,   20,   20,   20, 0x05,
      63,   20,   20,   20, 0x05,

 // slots: signature, parameters, type, tag, flags
      90,   87,   20,   20, 0x08,
     114,   20,   20,   20, 0x08,
     135,   87,   20,   20, 0x08,
     160,   87,   20,   20, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_TicTacToeGameWindow[] = {
    "TicTacToeGameWindow\0\0sendMoveRequest()\0"
    "sendP1EngineMove(Game*)\0sendP2EngineMove(Game*)\0"
    "id\0boardButtonHandler(int)\0"
    "recieveMoveRequest()\0receiveP1EngineMove(int)\0"
    "receiveP2EngineMove(int)\0"
};

void TicTacToeGameWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        TicTacToeGameWindow *_t = static_cast<TicTacToeGameWindow *>(_o);
        switch (_id) {
        case 0: _t->sendMoveRequest(); break;
        case 1: _t->sendP1EngineMove((*reinterpret_cast< Game*(*)>(_a[1]))); break;
        case 2: _t->sendP2EngineMove((*reinterpret_cast< Game*(*)>(_a[1]))); break;
        case 3: _t->boardButtonHandler((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->recieveMoveRequest(); break;
        case 5: _t->receiveP1EngineMove((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->receiveP2EngineMove((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData TicTacToeGameWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject TicTacToeGameWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_TicTacToeGameWindow,
      qt_meta_data_TicTacToeGameWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TicTacToeGameWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TicTacToeGameWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TicTacToeGameWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TicTacToeGameWindow))
        return static_cast<void*>(const_cast< TicTacToeGameWindow*>(this));
    return QWidget::qt_metacast(_clname);
}

int TicTacToeGameWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void TicTacToeGameWindow::sendMoveRequest()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void TicTacToeGameWindow::sendP1EngineMove(Game * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void TicTacToeGameWindow::sendP2EngineMove(Game * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
