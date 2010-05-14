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

#ifndef QGAMACORE__PROJECTSTREEWIDGET_H
#define QGAMACORE__PROJECTSTREEWIDGET_H

#include <QTreeWidget>
#include <QWidget>
#include <QContextMenuEvent>
#include <QAction>

#include "projectsmanager.h"
#include "../utils/applicationcomponentprovider.h"
#include "../preferences/settings.h"
#include "project.h"


namespace QGamaCore {

    // forward declarations
    class MainWindow;


    /**
      *
      */
    class ProjectsTreeWidget : public QTreeWidget
    {
        friend class Project;

        Q_OBJECT

        public:  
            ProjectsTreeWidget(QWidget *parent);
            ~ProjectsTreeWidget();

            void addProjectItem(Project *project);
            void deleteProjectItem(Project *project);
            void setProjectItemActive(Project *project);

            void addFileItems(Project *project, bool highlightOpened = true);

            void collapseNonActiveProjects();

            void renameItem(Project *project, const QString &fileCategoryId, int fileId, const QString &newName);
            void addFileItem(Project *project, const File &file, const QString &fileCategoryId, bool highlightOpened = true);
            void addSettingItem(Project *project, const AdjustmentSetting &adjustmentSetting, bool hihglightOpened = true);

        protected:
            void contextMenuEvent(QContextMenuEvent *event);

        private:
            QGamaCore::ProjectsManager *prm;
            QGamaCore::Settings *settings;
            QGamaCore::ApplicationComponentProvider *acp;

            QTreeWidgetItem* findProjectItem(Project *project);
            QTreeWidgetItem* findFileCategoryItem(Project *project, const QString &fileCategoryId);
            QTreeWidgetItem* findFileItem(Project *project, const QString &fileCategoryId, int fileId);

            void cancelAllHighlightings();
            void highlightActiveProject(QTreeWidgetItem *item);

            QGamaCore::MainWindow *mw;

        signals:
            void updateFileMenuEntries(Project *project);

        private slots:
            void openFileDoubleClick(QTreeWidgetItem *current, int);
            void processContextMenuAction(QAction *action);
            void changeActiveProject(QTreeWidgetItem *current, QTreeWidgetItem *previous);
        }; // class ProjectsTreeWidget

} // namespace QGamaCore

#endif // QGAMACORE__PROJECTSTREEWIDGET_H
