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

#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QTextEdit>


namespace QGamaCore {

    /**
      *
      */
    class TextEditor : public QTextEdit
    {
        Q_OBJECT

        public:
            TextEditor();
            ~TextEditor();

            void newFile();
            bool loadFile(const QString &fileName);
            bool save();
            bool saveAs();
            bool saveFile(const QString &fileName);
            QString userFriendlyCurrentFile();
            QString currentFile() { return curFile; }

        protected:
            void closeEvent(QCloseEvent *event);

        private slots:
            void documentWasModified();

        private:
            bool maybeSave();
            void setCurrentFile(const QString &fileName);
            QString strippedName(const QString &fullFileName);

            QString curFile;
            bool isUntitled;
    }; // class TextEditor

} // namespace QGamaCore


#endif // TEXTEDITOR_H
