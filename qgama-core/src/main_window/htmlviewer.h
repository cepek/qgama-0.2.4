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

#ifndef QGAMACORE__HTMLVIEWER_H
#define QGAMACORE__HTMLVIEWER_H

#include <QWebView>
#include <QString>

#include "document.h"
#include "../projects_manager/project.h"


namespace QGamaCore {

    /**
      *
      */
    class HtmlViewer : public Document
    {
        public:
            HtmlViewer(const QString &type, Project *pr);
            ~HtmlViewer();
            virtual QString getContent();
            virtual void setContent(const QString &content);

        protected:
            virtual void initializeUi();
            virtual bool isDocumentModified() { return true; }

        private:
            QWebView htmlViewer;
    }; // class HtmlViewer

} // namespace

#endif // QGAMACORE__HTMLVIEWER_H
