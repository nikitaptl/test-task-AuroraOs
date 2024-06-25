/****************************************************************************
** Meta object code from reading C++ file 'SharingFramework.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../library/SharingFramework.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SharingFramework.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SharingFramework_t {
    QByteArrayData data[20];
    char stringdata0[230];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SharingFramework_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SharingFramework_t qt_meta_stringdata_SharingFramework = {
    {
QT_MOC_LITERAL(0, 0, 16), // "SharingFramework"
QT_MOC_LITERAL(1, 17, 15), // "D-Bus Interface"
QT_MOC_LITERAL(2, 33, 16), // "dbus.application"
QT_MOC_LITERAL(3, 50, 14), // "formatsChanged"
QT_MOC_LITERAL(4, 65, 0), // ""
QT_MOC_LITERAL(5, 66, 10), // "formatList"
QT_MOC_LITERAL(6, 77, 7), // "newFile"
QT_MOC_LITERAL(7, 85, 4), // "path"
QT_MOC_LITERAL(8, 90, 13), // "stopRequested"
QT_MOC_LITERAL(9, 104, 15), // "registerFormats"
QT_MOC_LITERAL(10, 120, 9), // "addFormat"
QT_MOC_LITERAL(11, 130, 6), // "format"
QT_MOC_LITERAL(12, 137, 12), // "deleteFormat"
QT_MOC_LITERAL(13, 150, 21), // "GetSupportedFileTypes"
QT_MOC_LITERAL(14, 172, 17), // "createServiceFile"
QT_MOC_LITERAL(15, 190, 4), // "args"
QT_MOC_LITERAL(16, 195, 8), // "openFile"
QT_MOC_LITERAL(17, 204, 4), // "stop"
QT_MOC_LITERAL(18, 209, 12), // "writeMessage"
QT_MOC_LITERAL(19, 222, 7) // "message"

    },
    "SharingFramework\0D-Bus Interface\0"
    "dbus.application\0formatsChanged\0\0"
    "formatList\0newFile\0path\0stopRequested\0"
    "registerFormats\0addFormat\0format\0"
    "deleteFormat\0GetSupportedFileTypes\0"
    "createServiceFile\0args\0openFile\0stop\0"
    "writeMessage\0message"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SharingFramework[] = {

 // content:
       8,       // revision
       0,       // classname
       1,   14, // classinfo
      11,   16, // methods
       1,   98, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // classinfo: key, value
       1,    2,

 // signals: name, argc, parameters, tag, flags
       3,    1,   71,    4, 0x06 /* Public */,
       6,    1,   74,    4, 0x06 /* Public */,
       8,    0,   77,    4, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    1,   78,    4, 0x0a /* Public */,
      10,    1,   81,    4, 0x0a /* Public */,
      12,    1,   84,    4, 0x0a /* Public */,
      13,    0,   87,    4, 0x0a /* Public */,
      14,    1,   88,    4, 0x0a /* Public */,
      16,    1,   91,    4, 0x0a /* Public */,
      17,    0,   94,    4, 0x0a /* Public */,
      18,    1,   95,    4, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QStringList,    5,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void,

 // slots: parameters
    QMetaType::QString, QMetaType::QStringList,    5,
    QMetaType::QString, QMetaType::QString,   11,
    QMetaType::QString, QMetaType::QString,   11,
    QMetaType::QStringList,
    QMetaType::QString, QMetaType::QStringList,   15,
    QMetaType::QString, QMetaType::QString,    7,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   19,

 // properties: name, type, flags
       5, QMetaType::QStringList, 0x00495003,

 // properties: notify_signal_id
       0,

       0        // eod
};

void SharingFramework::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SharingFramework *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->formatsChanged((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 1: _t->newFile((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->stopRequested(); break;
        case 3: { QString _r = _t->registerFormats((*reinterpret_cast< QStringList(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 4: { QString _r = _t->addFormat((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 5: { QString _r = _t->deleteFormat((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 6: { QStringList _r = _t->GetSupportedFileTypes();
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = std::move(_r); }  break;
        case 7: { QString _r = _t->createServiceFile((*reinterpret_cast< QStringList(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 8: { QString _r = _t->openFile((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 9: _t->stop(); break;
        case 10: _t->writeMessage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SharingFramework::*)(QStringList );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharingFramework::formatsChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SharingFramework::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharingFramework::newFile)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SharingFramework::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SharingFramework::stopRequested)) {
                *result = 2;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<SharingFramework *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QStringList*>(_v) = _t->formatList(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<SharingFramework *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->registerFormats(*reinterpret_cast< QStringList*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject SharingFramework::staticMetaObject = { {
    QMetaObject::SuperData::link<QDBusAbstractAdaptor::staticMetaObject>(),
    qt_meta_stringdata_SharingFramework.data,
    qt_meta_data_SharingFramework,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SharingFramework::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SharingFramework::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SharingFramework.stringdata0))
        return static_cast<void*>(this);
    return QDBusAbstractAdaptor::qt_metacast(_clname);
}

int SharingFramework::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDBusAbstractAdaptor::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 1;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void SharingFramework::formatsChanged(QStringList _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SharingFramework::newFile(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void SharingFramework::stopRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
