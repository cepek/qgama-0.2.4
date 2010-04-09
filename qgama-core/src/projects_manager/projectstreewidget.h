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

#ifndef PROJECTSTREEWIDGET_H
#define PROJECTSTREEWIDGET_H

#include <QTreeWidget>
#include <QWidget>
#include <QContextMenuEvent>
#include <QAction>

#include "projectsmanager.h"
#include "../preferences/settings.h"
#include "project.h"


namespace QGamaCore {

    class ProjectsTreeWidget : public QTreeWidget
    {
        Q_OBJECT

        public:
            enum { Id=32, ProjectLocation=33, FileType=34, ProjectFilePath=35, FileOpened=36, FilePath=37 };
        
            ProjectsTreeWidget(QWidget *parent);
            ~ProjectsTreeWidget();

            void addProjectItem(const QString &projectName, const QString &projectLocation, bool markAsActive);
            void deleteProjectItem(const QString &projectName, const QString &projectLocation);

            void setProjectItemActive(const QString &projectName, const QString &projectLocation);

            void addFileItems(Project *project);

            void collapseNonActiveProjects();

        protected:
            void contextMenuEvent(QContextMenuEvent *event);

        private:
            QGamaCore::ProjectsManager *prm;
            QGamaCore::Settings *settings;

            QTreeWidgetItem* findProjectItem(const QString &projectName, const QString &projectLocation);
            QTreeWidgetItem* findFileCategoryItem(const QString &projectName, const QString &projectLocation, const QString &fileCategoryId);

            void cancelAllHighlightings();
            void highlightActiveProject(QTreeWidgetItem *item);
            void highlightActiveFile(QTreeWidgetItem *item);      

        private slots:
            void openFileDoubleClick(QTreeWidgetItem *current, int);
            void processContextMenuAction(QAction *action);
            void changeActiveProject(QTreeWidgetItem *current, QTreeWidgetItem *previous);
        }; // class ProjectsTreeWidget

} // namespace QGamaCore

#endif // PROJECTSTREEWIDGET_H
