/****************************************************************************
** Meta object code from reading C++ file 'fullscreenwidget.h'
**
** Created: Fri Jan 7 10:07:04 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "fullscreenwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fullscreenwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_fullScreenWidget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x0a,
      30,   17,   17,   17, 0x0a,
      43,   17,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_fullScreenWidget[] = {
    "fullScreenWidget\0\0pauseSlot()\0"
    "resumeSlot()\0stopSlot()\0"
};

const QMetaObject fullScreenWidget::staticMetaObject = {
    { &QGraphicsView::staticMetaObject, qt_meta_stringdata_fullScreenWidget,
      qt_meta_data_fullScreenWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &fullScreenWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *fullScreenWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *fullScreenWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_fullScreenWidget))
        return static_cast<void*>(const_cast< fullScreenWidget*>(this));
    return QGraphicsView::qt_metacast(_clname);
}

int fullScreenWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: pauseSlot(); break;
        case 1: resumeSlot(); break;
        case 2: stopSlot(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
