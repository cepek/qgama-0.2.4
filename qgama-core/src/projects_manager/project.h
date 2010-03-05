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

#ifndef PROJECT_H
#define PROJECT_H

#include <QString>
#include <QStringList>

namespace QGamaCore {

    class Project
    {
        private:
            QString name;
            QString location;
            QString outputType;
            QStringList files;
            bool mainProject;
            bool opened;

        public:
            Project() { opened=false; mainProject=false; }
            Project(const QString &name, const QString &location, bool mainProject);

            // setters
            void setMainProject(bool mainProject) { this->mainProject = mainProject; }
            void setOpened(bool opened) { this->opened = opened; }
            void setName(const QString &name) { this->name = name; }
            void setLocation(const QString &location) { this->location = location; }

            // getters
            bool isMainProject() { return mainProject; }
            bool isOpened() { return opened; }
            QString getLocation() { return location; }
            QString getName() { return name; }
    }; // class Project

} // namespace QGamaCore


#endif // PROJECT_H
