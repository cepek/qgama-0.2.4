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

#ifndef QGAMACORE__APPLICATIONCOMPONENTPROVIDER_H
#define QGAMACORE__APPLICATIONCOMPONENTPROVIDER_H

#include <QString>
#include <QWidget>
#include <QMdiSubWindow>

#include "../plugins_manager/pluginsmanagerdialog.h"
#include "../main_window/mainwindow.h"
#include "../projects_manager/projectstreewidget.h"


namespace QGamaCore {

    // defining object names of some important widgets
    const QString OBJECT_NAME_PLUGINS_MANAGER_DIALOG = "PluginsManagerDialog";
    const QString OBJECT_NAME_MAIN_WINDOW = "MainWindow";
    const QString OBJECT_NAME_PROJECTS_TREE_WIDGET = "treeWidget_Projects";


    /** Class containing static methods used all over the rest of the application.
      *
      */
    class ApplicationComponentProvider
    {
        private:
            ApplicationComponentProvider(); // forbidden (class contains only static methods)

        public:
            static PluginsManagerDialog* getPluginsManagerDialog();
            static MainWindow* getMainWindow();
            static ProjectsTreeWidget* getProjectsTreeWidget();

            static QWidget* findTopLevelWidget(const QString &name);
            static QWidget* findWidget(const QString &name);
            static QMdiSubWindow* findMdiSubWindow(const QString &file);
    }; // class Utils

} // namespace QGamaCore


#endif // QGAMACORE__APPLICATIONCOMPONENTPROVIDER_H
