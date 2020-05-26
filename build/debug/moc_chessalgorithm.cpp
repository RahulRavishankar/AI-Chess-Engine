/****************************************************************************
** Meta object code from reading C++ file 'chessalgorithm.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../ChessEngine/chessalgorithm.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'chessalgorithm.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ChessAlgorithm_t {
    QByteArrayData data[18];
    char stringdata0[177];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ChessAlgorithm_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ChessAlgorithm_t qt_meta_stringdata_ChessAlgorithm = {
    {
QT_MOC_LITERAL(0, 0, 14), // "ChessAlgorithm"
QT_MOC_LITERAL(1, 15, 12), // "boardChanged"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 11), // "ChessBoard*"
QT_MOC_LITERAL(4, 41, 8), // "gameOver"
QT_MOC_LITERAL(5, 50, 6), // "Result"
QT_MOC_LITERAL(6, 57, 20), // "currentPlayerChanged"
QT_MOC_LITERAL(7, 78, 6), // "Player"
QT_MOC_LITERAL(8, 85, 7), // "newGame"
QT_MOC_LITERAL(9, 93, 6), // "result"
QT_MOC_LITERAL(10, 100, 13), // "currentPlayer"
QT_MOC_LITERAL(11, 114, 8), // "NoResult"
QT_MOC_LITERAL(12, 123, 11), // "Player1Wins"
QT_MOC_LITERAL(13, 135, 4), // "Draw"
QT_MOC_LITERAL(14, 140, 11), // "Player2Wins"
QT_MOC_LITERAL(15, 152, 8), // "NoPlayer"
QT_MOC_LITERAL(16, 161, 7), // "Player1"
QT_MOC_LITERAL(17, 169, 7) // "Player2"

    },
    "ChessAlgorithm\0boardChanged\0\0ChessBoard*\0"
    "gameOver\0Result\0currentPlayerChanged\0"
    "Player\0newGame\0result\0currentPlayer\0"
    "NoResult\0Player1Wins\0Draw\0Player2Wins\0"
    "NoPlayer\0Player1\0Player2"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ChessAlgorithm[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       2,   44, // properties
       2,   52, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       4,    1,   37,    2, 0x06 /* Public */,
       6,    1,   40,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   43,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void, 0x80000000 | 7,    2,

 // slots: parameters
    QMetaType::Void,

 // properties: name, type, flags
       9, 0x80000000 | 5, 0x00095009,
      10, 0x80000000 | 7, 0x00495009,

 // properties: notify_signal_id
       0,
       2,

 // enums: name, alias, flags, count, data
       5,    5, 0x0,    4,   62,
       7,    7, 0x0,    3,   70,

 // enum data: key, value
      11, uint(ChessAlgorithm::NoResult),
      12, uint(ChessAlgorithm::Player1Wins),
      13, uint(ChessAlgorithm::Draw),
      14, uint(ChessAlgorithm::Player2Wins),
      15, uint(ChessAlgorithm::NoPlayer),
      16, uint(ChessAlgorithm::Player1),
      17, uint(ChessAlgorithm::Player2),

       0        // eod
};

void ChessAlgorithm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ChessAlgorithm *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->boardChanged((*reinterpret_cast< ChessBoard*(*)>(_a[1]))); break;
        case 1: _t->gameOver((*reinterpret_cast< Result(*)>(_a[1]))); break;
        case 2: _t->currentPlayerChanged((*reinterpret_cast< Player(*)>(_a[1]))); break;
        case 3: _t->newGame(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< ChessBoard* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ChessAlgorithm::*)(ChessBoard * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChessAlgorithm::boardChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ChessAlgorithm::*)(Result );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChessAlgorithm::gameOver)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ChessAlgorithm::*)(Player );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChessAlgorithm::currentPlayerChanged)) {
                *result = 2;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<ChessAlgorithm *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< Result*>(_v) = _t->result(); break;
        case 1: *reinterpret_cast< Player*>(_v) = _t->currentPlayer(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject ChessAlgorithm::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ChessAlgorithm.data,
    qt_meta_data_ChessAlgorithm,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ChessAlgorithm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ChessAlgorithm::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ChessAlgorithm.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ChessAlgorithm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 2;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void ChessAlgorithm::boardChanged(ChessBoard * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ChessAlgorithm::gameOver(Result _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ChessAlgorithm::currentPlayerChanged(Player _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
