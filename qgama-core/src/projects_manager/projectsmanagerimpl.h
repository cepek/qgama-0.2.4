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

#ifndef PROJECTSMANAGERIMPL_H
#define PROJECTSMANAGERIMPL_H

#include <QList>
#include <QTreeWidgetItem>

#include "projectsmanager.h"
#include "project.h"
#include "../preferences/settings.h"


namespace QGamaCore {

    class MainWindow;
    class ProjectsTreeWidget;


    /**
      *
      */
    class ProjectsManagerImpl : public ProjectsManager
    {
        friend class Factory;

        private:

            /// Pointer to the QGamaCore::ProjectsManagerImpl object.
            static ProjectsManagerImpl *self;                       // singleton

            ProjectsManagerImpl();                                  // forbidden

            /// Private operator= (singleton implementation).
            ProjectsManagerImpl& operator=(ProjectsManagerImpl&);   // forbidden

            /// Private copy constructor (singleton implementation).
            ProjectsManagerImpl(const ProjectsManagerImpl&);        // forbidden

            ~ProjectsManagerImpl();                                 // forbidden

            /// Reference to QGamaCore::Settings.
            QGamaCore::Settings *settings;

            /// Counter of the active pointers.
            static int pointersCount;

            bool isProjectOpened(const QString &projectName, const QString &projectLocation);

        protected:

            static ProjectsManagerImpl* instance();
            void release();

        public:

            bool newProject(const QString &projectType, const QString &projectName, const QString &projectLocation);
            bool openProject(const QString &projectFilePath, bool markAsActive = true);

            void closeProject(Project *project);
            void closeActiveProject();

            Project* getActiveProject();
            Project* getProject(const QString &projectName, const QString &projectLocation);
            void setActiveProject(const QString &projectName, const QString &projectLocation, bool slotCall=false);

            void updateProjectFilesEntries();
    }; // class ProjectsManagerImpl

} // namespace QGamaCore


#endif // PROJECTSMANAGERIMPL_H
