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

#include <QApplication>
#include <QList>
#include <QPluginLoader>
#include <QObject>

#include "utils.h"

using namespace QGamaCore;


/** Function returning a pointer to the wanted top-level widget (window that is actually loaded
  * in the memory).
  *
  * Returns the corresponding pointer if found or null if there's not such object.
  *
  * @param[in] name     The objectName of the top-level widget we want to find.
  * @return             The pointer to the found top-level widget.
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
