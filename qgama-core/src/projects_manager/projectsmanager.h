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

#ifndef QGAMACORE__PROJECTSMANAGER_H
#define QGAMACORE__PROJECTSMANAGER_H

#include <QList>
#include <QTreeWidgetItem>

#include "project.h"


namespace QGamaCore {

    class ProjectsManager
    {
        friend class Factory;

        protected:
            QList<Project*> projects;

            virtual void release() = 0;

        public:
            QList<Project*> getProjectsList() { return projects; }
            int projectsCount() { return projects.size(); }

            virtual Project* getProject(const QString &projectName, const QString &projectLocation) = 0;
            virtual Project* getActiveProject() = 0;
            virtual void setActiveProject(const QString &projectName, const QString &projectLocation, bool slotCall=false) = 0;

            virtual bool newProject(const QString &projectType, const QString &projectName, const QString &projectLocation) = 0;
            virtual bool openProject(const QString &projectFilePath, bool markAsActive = true) = 0;

            virtual void closeProject(Project *project) = 0;
            virtual void closeActiveProject() = 0;

            virtual void updateProjectFilesEntries() = 0;
    }; // class ProjectsManager

} // namespace QGamaCore


#endif // QGAMACORE__PROJECTSMANAGER_H
