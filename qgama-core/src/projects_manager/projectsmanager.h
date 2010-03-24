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

#ifndef PROJECTSMANAGER_H
#define PROJECTSMANAGER_H

#include <QList>
#include <QTreeWidgetItem>

#include "project.h"


namespace QGamaCore {

    class ProjectsManager
    {
        protected:
            QList<Project*> projects;

        public:
            virtual bool newProject(const QString &name, const QString &location) = 0;
            virtual bool openProject(const QString &projectFile) = 0;
            virtual void closeProject(Project *project) = 0;
            virtual void closeActiveProject() = 0;
            virtual void setActiveProject(const QString &name, const QString locationb) = 0;
    }; // class ProjectsManager

} // namespace QGamaCore


#endif // PROJECTSMANAGER_H
