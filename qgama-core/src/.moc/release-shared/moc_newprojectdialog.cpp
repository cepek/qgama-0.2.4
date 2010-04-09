/****************************************************************************
** Meta object code from reading C++ file 'newprojectdialog.h'
**
** Created: Thu Mar 25 00:06:12 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../projects_manager/newprojectdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'newprojectdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QGamaCore__NewProjectDialog[] = {

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
      29,   28,   28,   28, 0x08,
      60,   28,   28,   28, 0x08,
     106,   28,   28,   28, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QGamaCore__NewProjectDialog[] = {
    "QGamaCore::NewProjectDialog\0\0"
    "on_toolButton_Browse_clicked()\0"
    "on_lineEdit_Project_Name_textChanged(QString)\0"
    "createProject()\0"
};

const QMetaObject QGamaCore::NewProjectDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QGamaCore__NewProjectDialog,
      qt_meta_data_QGamaCore__NewProjectDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QGamaCore::NewProjectDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QGamaCore::NewProjectDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QGamaCore::NewProjectDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QGamaCore__NewProjectDialog))
        return static_cast<void*>(const_cast< NewProjectDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int QGamaCore::NewProjectDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_toolButton_Browse_clicked(); break;
        case 1: on_lineEdit_Project_Name_textChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: createProject(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
