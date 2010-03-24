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

    class ProjectsManagerImpl : public ProjectsManager
    {
        private:
            /// Pointer to the QGamaCore::ProjectsManagerImpl object.
            static ProjectsManagerImpl *self;                       // singleton

            ProjectsManagerImpl();                                  // forbidden

            /// Private operator= (singleton implementation).
            ProjectsManagerImpl& operator=(ProjectsManagerImpl&);   // forbidden

            /// Private copy constructor (singleton implementation).
            ProjectsManagerImpl(const ProjectsManagerImpl&);        // forbidden

            /// Reference to QGamaCore::Settings.
            QGamaCore::Settings &settings;

            Project* activeProject();

        public:
            /** Method returning a pointer to QGamaCore::ProjectsManagerImpl object.
              *
              * On the first call the instance is created, sequentially pointers to this instance are returned.
              */
            static ProjectsManagerImpl& instance() {
                if (self == 0)
                    self = new ProjectsManagerImpl();
                return *self;
            }

            /** Class destructor.
              *
              * Deletes dynamicaly created structures, that's object on the address by private instance pointer, set's the pointer
              * to null. Deletes also projects in the list.
              */
            ~ProjectsManagerImpl() {
                if (self != 0) {
                    delete self; self = 0;
                }

                for (int i=0; i<projects.size(); ++i) {
                    delete projects[i];
                }
            }  // destructor

            bool newProject(const QString &name, const QString &location);
            bool openProject(const QString &projectFile);

            void closeProject(Project *project);
            void closeActiveProject();

            void setActiveProject(const QString &name, QString location);
    }; // class ProjectsManagerImpl

} // namespace QGamaCore


#endif // PROJECTSMANAGERIMPL_H
