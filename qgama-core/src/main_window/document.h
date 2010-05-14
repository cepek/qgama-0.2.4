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

#ifndef QGAMACORE__DOCUMENT_H
#define QGAMACORE__DOCUMENT_H

#include <QString>
#include <QWidget>

#include "../projects_manager/project.h"
#include "../utils/applicationcomponentprovider.h"


namespace QGamaCore {

    // forward declarations
    class MainWindow;

    
    /**
      *
      */
    class Document : public QWidget
    {
        Q_OBJECT

        public:
            Document(const QString &type, Project *pr);
            ~Document();
            bool loadFile(const QString &fileName);
            bool save();
            bool saveAs();
            bool saveFile(const QString &fileName);
            QString userFriendlyCurrentFile();
            QString currentFile() { return curFile; }
            QString documentType() { return docType; }
            virtual QString getContent() = 0;
            virtual void setContent(const QString &content) = 0;
            void newFile(const QString &fileName, const QString &content);
            Project* getAsociatedProject() { return project; }

        signals:
            void saveStateChanged();

        protected slots:
            void modificationChanged(bool changed);

        private:
            bool maybeSave();
            void setCurrentFile(const QString &fileName);
            QString curFile;
            QString docType;
            QGamaCore::Project *project;
            QGamaCore::ApplicationComponentProvider *acp;

        protected:
            void closeEvent(QCloseEvent *event);
            QString strippedName(const QString &fullFileName);
            virtual bool isDocumentModified() { return false; }
            virtual void setDocumentModified(bool modified) { Q_UNUSED(modified) };
            virtual void initializeUi() = 0;

            MainWindow *mw;
    }; // class Document

} // namespace QGamaCore


#endif // QGAMACORE__DOCUMENT_H
