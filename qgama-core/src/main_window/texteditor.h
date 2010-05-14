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

#ifndef QGAMACORE__TEXTEDITOR_H
#define QGAMACORE__TEXTEDITOR_H

#include <QTextEdit>
#include <QLabel>

#include "document.h"
#include "../utils/xmlsyntaxhighlighter.h"
#include "../projects_manager/project.h"


namespace QGamaCore {

    /**
      *
      */
    class TextEditor : public Document
    {
        Q_OBJECT

        public:
            TextEditor(const QString &type, Project *pr);
            ~TextEditor();
            virtual QString getContent();
            virtual void setContent(const QString &content);
            void moveCursor(int line, int column) {
                // set the cursor to the initial position
                editor.moveCursor(QTextCursor::Start);

                // move the cursor to the corresponding line
                for (int i = 1; i < line; ++i)
                    editor.moveCursor(QTextCursor::Down);

                // move the cursor to the corresponding character position
                for (int i = 1; i < column; ++i)
                    editor.moveCursor(QTextCursor::Right);

                // set the selection of corresponding line
                QList<QTextEdit::ExtraSelection> extraSelections;
                QTextEdit::ExtraSelection selection;

                const QColor lineColor = QColor(Qt::red).lighter(160);
                selection.format.setBackground(lineColor);
                selection.format.setProperty(QTextFormat::FullWidthSelection, true);
                selection.cursor = editor.textCursor();
                selection.cursor.clearSelection();
                extraSelections.append(selection);

                editor.setExtraSelections(extraSelections);

                // set the focus
                editor.setFocus();
            }
            void clearHighlights() {
                QList<QTextEdit::ExtraSelection> selections;
                editor.setExtraSelections(selections);
            }
            void setLabelValidationText(const QString &text) { label_validation.setText(text); }
            void setLabelValidationStyleSheet(const QString &styleSheet) { label_validation.setStyleSheet(styleSheet); }

        protected:
            virtual bool isDocumentModified();
            virtual void setDocumentModified(bool modified);
            virtual void initializeUi();

        private:
            QTextEdit editor;
            XmlSyntaxHighlighter highlighter;
            QLabel label_status;
            QLabel label_validation;

        private slots:
            void textChanged();
    }; // class TextEditor

} // namespace QGamaCore


#endif // QGAMACORE__TEXTEDITOR_H
