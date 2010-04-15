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

#include "utils.h"
#include "../main_window/document.h"

#include <iostream>

using namespace QGamaCore;


/** Function returning a pointer to the wanted top-level widget (window that is actually loaded
  * in the memory).
  *
  * Returns the corresponding pointer if found or null if there's not such object.
  *
  * @param[in] name     The objectName of the top-level widget we want to find.
  * @return             The pointer to the found top-level widget or null if not found.
  */
QWidget* Utils::findTopLevelWidget(const QString &name)
{
    // get the list of active top-level widgets
    QList<QWidget*> windows = qApp->topLevelWidgets();
    // find the first one corresponding to the specified object name and return it's pointer if found
    for (QList<QWidget*>::iterator i=windows.begin(); i!=windows.end(); ++i) {        
        if ((*i)->objectName()==name) {
            return *i;
        }
    }

    // otherwise return null
    return 0;
}


/** Function returning a pointer to the wanted widget (widget that is actually loaded
  * in the memory).
  *
  * Returns the corresponding pointer if found or null if there's not such object.
  *
  * @param[in] name     The objectName of the widget we want to find.
  * @return             The pointer to the found widget or null if not found.
  */
QWidget* Utils::findWidget(const QString &name)
{
    // get the list of active top-level widgets
    QList<QWidget*> windows = qApp->allWidgets();
    // find the first one corresponding to the specified object name and return it's pointer if found
    for (QList<QWidget*>::iterator i=windows.begin(); i!=windows.end(); ++i) {
        if ((*i)->objectName()==name) {
            return *i;
        }
    }

    // otherwise return null
    return 0;
}


/** Function returning a pointer to the wanted subwindow.
  *
  * Returns the corresponding pointer if found or null if there's not such object.
  *
  * @param[in] name     The path of the opened file we want to find.
  * @return             The pointer to the found subwindow.
  */
QMdiSubWindow* Utils::findMdiSubWindow(const QString &file)
{
    // get the cannonical file path
    QString filePath = QFileInfo(file).canonicalFilePath();

    // get the list of all active subwindows of mdiArea
    QMdiArea *mdiArea = qobject_cast<QMdiArea*> (findWidget("mdiArea"));
    QList<QMdiSubWindow*> subWindows = mdiArea->subWindowList();

    // iterate through subwindows list, find the corresponding file
    for (QList<QMdiSubWindow*>::iterator i=subWindows.begin(); i!=subWindows.end(); ++i) {
        Document *mdiChild = qobject_cast<Document*> ((*i)->widget());
        // if exists, return its pointer
        if (mdiChild->currentFile() == filePath)
            return *i;
    }

    // otherwise return null
    return 0;
}
