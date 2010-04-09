/****************************************************************************
** Meta object code from reading C++ file 'projectstreewidget.h'
**
** Created: Thu Mar 25 00:06:13 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../projects_manager/projectstreewidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'projectstreewidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QGamaCore__ProjectsTreeWidget[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      36,   31,   30,   30, 0x05,

 // slots: signature, parameters, type, tag, flags
      71,   54,   30,   30, 0x0a,
     135,  126,   30,   30, 0x08,
     184,  177,   30,   30, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QGamaCore__ProjectsTreeWidget[] = {
    "QGamaCore::ProjectsTreeWidget\0\0file\0"
    "openFile(QString)\0current,previous\0"
    "changeActiveProject(QTreeWidgetItem*,QTreeWidgetItem*)\0"
    "current,\0openFileDoubleClick(QTreeWidgetItem*,int)\0"
    "action\0processContextMenuAction(QAction*)\0"
};

const QMetaObject QGamaCore::ProjectsTreeWidget::staticMetaObject = {
    { &QTreeWidget::staticMetaObject, qt_meta_stringdata_QGamaCore__ProjectsTreeWidget,
      qt_meta_data_QGamaCore__ProjectsTreeWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QGamaCore::ProjectsTreeWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QGamaCore::ProjectsTreeWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QGamaCore::ProjectsTreeWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QGamaCore__ProjectsTreeWidget))
        return static_cast<void*>(const_cast< ProjectsTreeWidget*>(this));
    return QTreeWidget::qt_metacast(_clname);
}

int QGamaCore::ProjectsTreeWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTreeWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: openFile((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: changeActiveProject((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< QTreeWidgetItem*(*)>(_a[2]))); break;
        case 2: openFileDoubleClick((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: processContextMenuAction((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void QGamaCore::ProjectsTreeWidget::openFile(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
