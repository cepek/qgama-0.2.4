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

#include <QFile>
#include <QCloseEvent>
#include <QApplication>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>

#include "texteditor.h"
#include "../utils/utils.h"
#include "mainwindow.h"

using namespace QGamaCore;


TextEditor::TextEditor()
{
    // makes Qt delete this widget when the widget has accepted the close event (see QWidget::closeEvent())
    setAttribute(Qt::WA_DeleteOnClose);
    // sets document as untitled after it's creation
    isUntitled = true;
}


TextEditor::~TextEditor()
{
    MainWindow *mw = qobject_cast<MainWindow*> (Utils::findTopLevelWidget("MainWindow"));
    mw->setWindowTitle(mw->windowTitle().split(" - ").value(0).trimmed());
}


void TextEditor::newFile()
{
    static int sequenceNumber = 1;
    isUntitled = true;
    curFile = tr("Untitled_TextEditor_%1.gfk").arg(sequenceNumber++);
    setWindowTitle(curFile+"[*]");

    MainWindow *mw = qobject_cast<MainWindow*> (Utils::findTopLevelWidget("MainWindow"));
    mw->setWindowTitle(mw->windowTitle()+" - "+curFile+"[*]");

    connect(document(), SIGNAL(contentsChanged()), this, SLOT(documentWasModified()));
}


bool TextEditor::loadFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("MDI"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return false;
    }

    QTextStream in(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    setPlainText(in.readAll());
    QApplication::restoreOverrideCursor();

    setCurrentFile(fileName);

    connect(document(), SIGNAL(contentsChanged()), this, SLOT(documentWasModified()));

    return true;
}


bool TextEditor::save()
{
    if (isUntitled) {
        return saveAs();
    } else {
        return saveFile(curFile);
    }
}


bool TextEditor::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
                                                    curFile);
    if (fileName.isEmpty())
        return false;

    return saveFile(fileName);
}


bool TextEditor::saveFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("MDI"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return false;
    }

    QTextStream out(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    out << toPlainText();
    QApplication::restoreOverrideCursor();

    setCurrentFile(fileName);
    return true;
}


QString TextEditor::userFriendlyCurrentFile()
{
    return strippedName(curFile);
}


void TextEditor::closeEvent(QCloseEvent *event)
{
    if (maybeSave()) {
        event->accept();
    } else {
        event->ignore();
    }
}


void TextEditor::documentWasModified()
{
    setWindowModified(document()->isModified());

    MainWindow *mw = dynamic_cast<MainWindow*> (Utils::findTopLevelWidget("MainWindow"));
    mw->setWindowModified(document()->isModified());
}


bool TextEditor::maybeSave()
{
    if (document()->isModified()) {
        QMessageBox::StandardButton ret;
        ret = QMessageBox::warning(this, tr("MDI"),
                     tr("'%1' has been modified.\n"
                        "Do you want to save your changes?")
                     .arg(userFriendlyCurrentFile()),
                     QMessageBox::Save | QMessageBox::Discard
                     | QMessageBox::Cancel);
        if (ret == QMessageBox::Save)
            return save();
        else if (ret == QMessageBox::Cancel)
            return false;
    }
    return true;
}


void TextEditor::setCurrentFile(const QString &fileName)
{
    curFile = QFileInfo(fileName).canonicalFilePath();
    isUntitled = false;
    document()->setModified(false);
    setWindowModified(false);
    setWindowTitle(userFriendlyCurrentFile() + "[*]");
}


QString TextEditor::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}
