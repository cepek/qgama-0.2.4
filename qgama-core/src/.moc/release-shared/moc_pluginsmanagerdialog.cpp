/****************************************************************************
** Meta object code from reading C++ file 'pluginsmanagerdialog.h'
**
** Created: Wed Mar 24 23:04:41 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../plugins_manager/pluginsmanagerdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pluginsmanagerdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QGamaCore__PluginsManagerDialog[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      50,   33,   32,   32, 0x08,
     126,   32,   32,   32, 0x08,
     150,   32,   32,   32, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QGamaCore__PluginsManagerDialog[] = {
    "QGamaCore::PluginsManagerDialog\0\0"
    "current,previous\0"
    "on_treeWidget_Plugins_currentItemChanged(QTreeWidgetItem*,QTreeWidgetI"
    "tem*)\0"
    "on_buttonBox_accepted()\0on_toolButton_clicked()\0"
};

const QMetaObject QGamaCore::PluginsManagerDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QGamaCore__PluginsManagerDialog,
      qt_meta_data_QGamaCore__PluginsManagerDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QGamaCore::PluginsManagerDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QGamaCore::PluginsManagerDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QGamaCore::PluginsManagerDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QGamaCore__PluginsManagerDialog))
        return static_cast<void*>(const_cast< PluginsManagerDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int QGamaCore::PluginsManagerDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_treeWidget_Plugins_currentItemChanged((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< QTreeWidgetItem*(*)>(_a[2]))); break;
        case 1: on_buttonBox_accepted(); break;
        case 2: on_toolButton_clicked(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
