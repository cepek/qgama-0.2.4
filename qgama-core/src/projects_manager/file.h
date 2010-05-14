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

#ifndef QGAMACORE__FILE_H
#define QGAMACORE__FILE_H

#include <QString>


namespace QGamaCore {

    /**
      *
      */
    class File
    {
        private:
            QString name;
            QString path;
            QString opened;
            QString format;
            int settingsId;
            int id;
            bool displayed;

        public:
            File() { displayed=false; }
            ~File() {}

            // setters
            void setName(const QString &name)       { this->name=name; }
            void setPath(const QString &path)       { this->path=path; }
            void setOpened(const QString &opened)   { this->opened=opened; }
            void setFormat(const QString &format)   { this->format=format; }
            void setSettingsId(int settingsId)      { this->settingsId=settingsId; }
            void setId(int id)                      { this->id=id; }
            void setDisplayed(bool displayed)       { this->displayed=displayed; }

            // getters
            QString getName() const     { return name; }
            QString getPath() const     { return path; }
            QString getOpened() const   { return opened; }
            QString getFormat() const   { return format; }
            int getSettingsId() const   { return settingsId; }
            int getId() const           { return id; }
            bool isDisplayed() const    { return displayed; }
    }; // class File

} // namespace QGamaCore


#endif // QGAMACORE__FILE_H
