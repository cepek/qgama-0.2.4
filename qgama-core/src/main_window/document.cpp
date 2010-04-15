#include <QtGui>

#include "mainwindow.h"

#include "document.h"
#include "../utils/utils.h"

using namespace QGamaCore;


/* ===============================================================================================================*/
/**
  *
  */
Document::Document(const QString &type) :
    docType(type),
    mw(qobject_cast<MainWindow*> (Utils::findTopLevelWidget("MainWindow")))
{
    connect(this, SIGNAL(saveStateChanged()), mw, SLOT(subWindowsStatesChanged()));
}


/* ===============================================================================================================*/
/**
  *
  */
Document::~Document()
{

}


/* ===============================================================================================================*/
/**
  *
  */
QString Document::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}


/* ===============================================================================================================*/
/**
  *
  */

void Document::modificationChanged(bool changed) {
    // add asterisk to window title
    getWidget()->setWindowModified(changed);
    mw->setWindowModified(changed);

    emit saveStateChanged();
}


/* ===============================================================================================================*/
/**
  *
  */
void Document::setCurrentFile(const QString &fileName)
{
    curFile = QFileInfo(fileName).canonicalFilePath();

    //document()->setModified(false);

    getWidget()->setWindowTitle(userFriendlyCurrentFile()+"[*]");
    mw->setWindowTitle(mw->windowTitle().split(" - ").value(0).trimmed()+" - "+userFriendlyCurrentFile()+"[*]");

    emit modificationChanged(false);
}


/* ===============================================================================================================*/
/**
  *
  */
QString Document::userFriendlyCurrentFile()
{
    return strippedName(curFile);
}


bool Document::loadFile(const QString &fileName)
{
    // try to open the file
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(0 , tr("Error during opening file!"), tr("Cannot read file %1:\n%2.") .arg(fileName) .arg(file.errorString()));
        return false;
    }

    // read its content
    QTextStream in(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    setContent(in.readAll());
    QApplication::restoreOverrideCursor();

    // set the current file
    setCurrentFile(fileName);

    emit modificationChanged(false);

    return true;
}


/* ===============================================================================================================*/
/**
  *
  */
bool Document::save()
{
    return saveFile(curFile);
}


/* ===============================================================================================================*/
/**
  *
  */
bool Document::saveAs()
{
    // save as dialog
    QString fileName = QFileDialog::getSaveFileName(getWidget(), tr("Save As"), curFile);
    if (fileName.isEmpty())
        return false;

    return saveFile(fileName);
}


/* ===============================================================================================================*/
/**
  *
  */
bool Document::saveFile(const QString &fileName)
{
    // try to open the file
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(0, tr("Error during writing to file!"), tr("Cannot write file %1:\n%2.") .arg(fileName) .arg(file.errorString()));
        return false;
    }

    // set the document content in it
    QTextStream out(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    out << getContent();
    QApplication::restoreOverrideCursor();

    // set current file
    setCurrentFile(fileName);

    emit saveStateChanged();

    return true;
}


/* ===============================================================================================================*/
/**
  *
  */
bool Document::maybeSave()
{
    if (isModified()) {
        QMessageBox::StandardButton ret = QMessageBox::warning(0, tr("Unsaved changes!"), tr("'%1' has been modified.\nDo you want to save your changes?") .arg(userFriendlyCurrentFile()), QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        if (ret == QMessageBox::Save)
            return save();
        else if (ret == QMessageBox::Cancel)
            return false;
    }

    return true;
}


/* ===============================================================================================================*/
/**
  *
  */
void Document::closeEvent(QCloseEvent *event)
{
    mw->setWindowTitle(mw->windowTitle().split(" - ").value(0).trimmed());

    if (maybeSave()) {
        event->accept();
    } else {
        event->ignore();
    }
}
