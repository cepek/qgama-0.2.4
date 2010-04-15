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
#include <QDomDocument>

#include "adjustmentsetting.h"
#include "file.h"


namespace QGamaCore {

    class MainWindow;
    class ProjectsTreeWidget;


    /**
      *
      */
    class Project
    {
        private:
            QDomDocument xml;

            QString name;
            QString location;
            QString projectFilePath;

            QString type;
            bool active;

            QList<File> networks;
            QList<AdjustmentSetting> adjustmentSettings;

            int lastNetworksId;
            int lastSettingsId;
            int lastSolutionsId;

            bool loadXml();

            void createNetworkEntry(const File& network);
            void updateNetworkEntry(const File& network);
            void createAdjustmentSettingEntry(const AdjustmentSetting &as);
            void updateAdjustmentSettingEntry(const AdjustmentSetting &as);

            QGamaCore::MainWindow *mw;
            QGamaCore::ProjectsTreeWidget *ptw;

            static bool createSingleNetworkProjectStructure(const QString &type, const QString &name, const QString &location);

        public:
            Project(const QString &name, const QString &location, const QString &projectFilePath);
            ~Project();

            // setters
            void setActive(bool active)                             { this->active = active; }
            void setType(const QString &type)                       { this->type = type; }
            void setName(const QString &name)                       { this->name = name; }
            void setLocation(const QString &location)               { this->location = location; }
            void setProjectFilePath(const QString &projectFilePath) { this->projectFilePath = projectFilePath; }

            // getters
            bool    isActive()              { return active; }
            QString getType()               { return type; }
            QString getLocation()           { return location; }
            QString getName()               { return name; }
            QString getProjectFilePath()    { return projectFilePath; }
            int getNextNetworksId()         { return ++lastNetworksId; }
            int getNextSettingsId()         { return ++lastSettingsId; }
            int getNextSolutionsId()        { return ++lastSolutionsId; }

            QList<File>& getNetworks()      { return networks; }
            File*        getNetwork(int id);
            bool         newNetwork(const QString &filePath);
            bool         importNetwork(const QString &filePath);
            bool         linkNetwork(const QString &filePath);

            QList<AdjustmentSetting>& getAdjustmentSettings() { return adjustmentSettings; }
            AdjustmentSetting*        getAdjustmentSetting(int id);
            bool                      newAdjustmentSetting(AdjustmentSetting &as);

            // others
            void updateProjectFileEntries();
            static bool createProjectStructure(const QString &type, const QString &name, const QString &location);
    }; // class Project

} // namespace QGamaCore


#endif // PROJECT_H
