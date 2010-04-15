/*
    QGamaCore GUI C++ Library (QGamaCoreLib)
    Copyright (C) 2010  Jiri Novak <jiri.novak.2@fsv.cvut.cz>

    This file is part of the QGamaCore GUI C++ Library.

    This library is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include <QtGui>

#include "texteditor.h"
#include "../utils/utils.h"
#include "mainwindow.h"

#include <iostream>

using namespace QGamaCore;


/* ===============================================================================================================*/
/**
  *
  */
TextEditor::TextEditor(const QString &type) :
    Document(type),
    editor(),
    highlighter(editor.document())
{
}


/* ===============================================================================================================*/
/**
  *
  */
TextEditor::~TextEditor()
{
}


/* ===============================================================================================================*/
/**
  *
  */
bool TextEditor::loadFile(const QString &fileName)
{
    // try to open the file
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Error during opening file!"), tr("Cannot read file %1:\n%2.") .arg(fileName) .arg(file.errorString()));
        return false;
    }

    // read its content
    QTextStream in(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    setPlainText(in.readAll());
    QApplication::restoreOverrideCursor();

    // set the current file
    setCurrentFile(fileName);

    connect(document(), SIGNAL(contentsChanged()), this, SLOT(documentWasModified()));
    connect(document(), SIGNAL(contentsChanged()), mw, SLOT(subWindowsStatesChanged()));
    connect(this, SIGNAL(saveStateChanged()), mw, SLOT(subWindowsStatesChanged()));

    emit saveStateChanged();

    return true;
}


/* ===============================================================================================================*/
/**
  *
  */
bool TextEditor::save()
{
    return saveFile(curFile);
}


/* ===============================================================================================================*/
/**
  *
  */
bool TextEditor::saveAs()
{
    std::cout << "saveAs START" << std::endl;
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
                                                    curFile);
    if (fileName.isEmpty())
        return false;

    std::cout << "saveAs STOP" << std::endl;

    return saveFile(fileName);
}


/* ===============================================================================================================*/
/**
  *
  */
bool TextEditor::saveFile(const QString &fileName)
{
    std::cout << "saveFile START" << std::endl;
    // try to open the file
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Error during writing to file!"), tr("Cannot write file %1:\n%2.") .arg(fileName) .arg(file.errorString()));
        return false;
    }

    QTextStream out(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    out << toPlainText();
    QApplication::restoreOverrideCursor();

    setCurrentFile(fileName);

    std::cout << "saveFile STOP" << std::endl;

    emit saveStateChanged();

    return true;
}


/* ===============================================================================================================*/
/**
  *
  */
QString TextEditor::userFriendlyCurrentFile()
{
    return strippedName(curFile);
}


/* ===============================================================================================================*/
/**
  *
  */
void TextEditor::closeEvent(QCloseEvent *event)
{
    mw->setWindowTitle(mw->windowTitle().split(" - ").value(0).trimmed());

    if (maybeSave()) {
        event->accept();
    } else {
        event->ignore();
    }

    std::cout << "tady bych ciste teoreticky mohl nacpat to ulozeni zmen o souboru" << std::endl;
}


/* ===============================================================================================================*/
/**
  *
  */
bool TextEditor::maybeSave()
{
    if (document()->isModified()) {
        QMessageBox::StandardButton ret = QMessageBox::warning(this,
                                                               tr("Unsaved changes!"),
                                                               tr("'%1' has been modified.\nDo you want to save your changes?")
                                                                    .arg(userFriendlyCurrentFile()),
                                                               QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
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
void TextEditor::documentWasModified()
{
    std::cout << "??" << std::endl;
    setWindowModified(document()->isModified());
    mw->setWindowModified(document()->isModified());
    std::cout << "???" << std::endl;
}


/* ===============================================================================================================*/
/**
  *
  */
void TextEditor::setCurrentFile(const QString &fileName)
{
    curFile = QFileInfo(fileName).canonicalFilePath();

    document()->setModified(false);

    setWindowModified(false);
    setWindowTitle(userFriendlyCurrentFile()+"[*]");

    mw->setWindowModified(false);
    mw->setWindowTitle(mw->windowTitle().split(" - ").value(0).trimmed()+" - "+userFriendlyCurrentFile()+"[*]");
}
