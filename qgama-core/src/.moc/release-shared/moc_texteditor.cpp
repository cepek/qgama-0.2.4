/****************************************************************************
** Meta object code from reading C++ file 'texteditor.h'
**
** Created: Wed Mar 24 20:36:33 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../main_window/texteditor.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'texteditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QGamaCore__TextEditor[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      23,   22,   22,   22, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QGamaCore__TextEditor[] = {
    "QGamaCore::TextEditor\0\0documentWasModified()\0"
};

const QMetaObject QGamaCore::TextEditor::staticMetaObject = {
    { &QTextEdit::staticMetaObject, qt_meta_stringdata_QGamaCore__TextEditor,
      qt_meta_data_QGamaCore__TextEditor, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QGamaCore::TextEditor::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QGamaCore::TextEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QGamaCore::TextEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QGamaCore__TextEditor))
        return static_cast<void*>(const_cast< TextEditor*>(this));
    return QTextEdit::qt_metacast(_clname);
}

int QGamaCore::TextEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTextEdit::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: documentWasModified(); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
