/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Thu Mar 25 00:06:10 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../main_window/mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QGamaCore__MainWindow[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      23,   22,   22,   22, 0x08,
      36,   22,   22,   22, 0x08,
      50,   22,   22,   22, 0x08,
      65,   22,   22,   22, 0x08,
      75,   22,   22,   22, 0x08,
      91,   86,   22,   22, 0x08,
     109,   22,   22,   22, 0x08,
     131,   22,   22,   22, 0x08,
     159,  151,   22,   22, 0x08,
     196,   22,   22,   22, 0x08,
     215,   22,   22,   22, 0x08,
     232,   22,   22,   22, 0x08,
     251,   22,   22,   22, 0x08,
     272,   22,   22,   22, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QGamaCore__MainWindow[] = {
    "QGamaCore::MainWindow\0\0newProject()\0"
    "openProject()\0closeProject()\0newFile()\0"
    "openFile()\0file\0openFile(QString)\0"
    "pluginManagerDialog()\0preferencesDialog()\0"
    "checked\0on_action_Toolbar_File_toggled(bool)\0"
    "openProjectsDock()\0openOutputDock()\0"
    "aboutQGamaDialog()\0aboutGnuGamaDialog()\0"
    "aboutQtDialog()\0"
};

const QMetaObject QGamaCore::MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_QGamaCore__MainWindow,
      qt_meta_data_QGamaCore__MainWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QGamaCore::MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QGamaCore::MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QGamaCore::MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QGamaCore__MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int QGamaCore::MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: newProject(); break;
        case 1: openProject(); break;
        case 2: closeProject(); break;
        case 3: newFile(); break;
        case 4: openFile(); break;
        case 5: openFile((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: pluginManagerDialog(); break;
        case 7: preferencesDialog(); break;
        case 8: on_action_Toolbar_File_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: openProjectsDock(); break;
        case 10: openOutputDock(); break;
        case 11: aboutQGamaDialog(); break;
        case 12: aboutGnuGamaDialog(); break;
        case 13: aboutQtDialog(); break;
        default: ;
        }
        _id -= 14;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
