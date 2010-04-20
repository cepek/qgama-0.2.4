#include <QtGui>

#include "mainwindow.h"

#include "document.h"
#include "../utils/applicationcomponentprovider.h"

using namespace QGamaCore;


/* ===============================================================================================================*/
/**
  *
  */
Document::Document(const QString &type, Project *pr) :
    docType(type),
    project(pr),
    mw(ApplicationComponentProvider::getMainWindow())
{
    setAttribute(Qt::WA_DeleteOnClose);
    connect(this, SIGNAL(saveStateChanged()), mw, SLOT(onSubWindowStateChanged()));
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
    if (!curFile.isEmpty()) {
        setWindowModified(changed);
        mw->setWindowModified(changed);
        setDocumentModified(changed);
    }

    emit saveStateChanged();
}


/* ===============================================================================================================*/
/**
  *
  */
void Document::setCurrentFile(const QString &fileName)
{
    curFile = fileName;

    setWindowTitle(userFriendlyCurrentFile()+"[*]");

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
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"), curFile);
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
    qDebug() << "Document::saveFile() START";
    // try to open the file
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Error during writing to file!"), tr("Cannot write file %1:\n%2.") .arg(fileName) .arg(file.errorString()));
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
    if (isDocumentModified()) {
        QMessageBox::StandardButton ret = QMessageBox::warning(this, tr("Unsaved changes!"), tr("'%1' has been modified.\nDo you want to save your changes?") .arg(userFriendlyCurrentFile()), QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
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
    if (maybeSave()) {
        event->accept();
    } else {
        event->ignore();
    }
}


bool Document::loadFile(const QString &fileName)
{
    // try to open the file
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this , tr("Error during opening file!"), tr("Cannot read file %1:\n%2.") .arg(fileName) .arg(file.errorString()));
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


void Document::newFile(const QString &fileName, const QString &content)
{
    qDebug() << "Document::newFile() - START";

    // set content
    setContent(content);

    qDebug() << "Document::newFile() - content set";

    // set the currentFile
    setCurrentFile(fileName);

    qDebug() << "Document::newFile() - fileName: " << curFile;
    qDebug() << "Document::newFile() - currentFile set to: " << curFile;

    emit modificationChanged(true);

    qDebug() << "Document::newFile() - STOP";
}
