/****************************************************************************
**
**    QGamaCore GUI C++ Library (QGamaCoreLib)
**    Copyright (C) 2010  Jiri Novak <jiri.novak.2@fsv.cvut.cz>
**
**    This file is part of the QGamaCore GUI C++ Library.
**
**    This library is free software; you can redistribute it and/or modify
**    it under the terms of the GNU General Public License as published by
**    the Free Software Foundation; either version 3 of the License, or
**    (at your option) any later version.
**
**    This library is distributed in the hope that it will be useful,
**    but WITHOUT ANY WARRANTY; without even the implied warranty of
**    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**    GNU General Public License for more details.
**
**    You should have received a copy of the GNU General Public License
**    along with this library; if not, write to the Free Software
**    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
**
****************************************************************************/

#include <QtGui>

#include "texteditor.h"
#include "../utils/applicationcomponentprovider.h"
#include "mainwindow.h"

using namespace QGamaCore;


/* ===============================================================================================================*/
/**
  *
  */
TextEditor::TextEditor(const QString &type, Project *pr) :
    Document(type, pr),
    editor(),
    highlighter(editor.document())
{
    // initialize Ui
    initializeUi();

    // make connections
    connect(editor.document(), SIGNAL(modificationChanged(bool)), this, SLOT(modificationChanged(bool)));
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
void TextEditor::setContent(const QString &content)
{
    editor.setPlainText(content);
}


/* ===============================================================================================================*/
/**
  *
  */
QString TextEditor::getContent()
{
    return editor.toPlainText();
}


/* ===============================================================================================================*/
/**
  *
  */
void TextEditor::setDocumentModified(bool modified)
{
    editor.document()->setModified(modified);
}


/* ===============================================================================================================*/
/**
  *
  */
bool TextEditor::isDocumentModified()
{
    return editor.document()->isModified();
}


/* ===============================================================================================================*/
/**
  *
  */
void TextEditor::initializeUi()
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setMargin(0);
    layout->addWidget(&editor,1);
    QHBoxLayout *verticalLayout = new QHBoxLayout();
    label_status.setText(tr("Status of validation: "));
    label_validation.setText(tr("Not Validated"));
    label_validation.setMargin(3);
    label_status.setVisible(false);
    label_validation.setVisible(false);
    verticalLayout->addWidget(&label_status,0);
    verticalLayout->addWidget(&label_validation,1);
    verticalLayout->setMargin(0);
    layout->addLayout(verticalLayout);
    setLayout(layout);

    if (documentType() == "network") {
        label_status.setVisible(true);
        label_validation.setVisible(true);
    }

    if (documentType() == "txt") {
        QFont font = qApp->font();
        font.setFamily("Courier");
        editor.setFont(font);
    }

    // makes Qt delete this widget when the widget has accepted the close event
    editor.setAttribute(Qt::WA_DeleteOnClose);
}


/* ===============================================================================================================*/
/**
  *
  */
void TextEditor::textChanged()
{
    editor.setExtraSelections(QList<QTextEdit::ExtraSelection>());
}
