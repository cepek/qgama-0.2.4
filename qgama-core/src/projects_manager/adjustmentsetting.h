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

#ifndef QGAMACORE__ADJUSTMENTSETTING_H
#define QGAMACORE__ADJUSTMENTSETTING_H

#include <QString>


namespace QGamaCore {

    /**
      *
      */
    class AdjustmentSetting
    {
        private:
            int id;
            QString algorithm;
            QString output;
            QString encoding;
            QString ellipsoid;
            QString language;
            QString covband;
            QString name;
            QString angles;
            QString latitude;
            bool displayed;

        public:
            AdjustmentSetting() { displayed=false; }
            ~AdjustmentSetting() {}

            // setters
            void setAlgorithm(const QString &algorithm) { this->algorithm=algorithm; }
            void setOutput(const QString &output)       { this->output=output; }
            void setEncoding(const QString &encoding)   { this->encoding=encoding; }
            void setEllipsoid(const QString &ellipsoid) { this->ellipsoid=ellipsoid; }
            void setLanguage(const QString &language)   { this->language=language; }
            void setCovband(const QString &covband)     { this->covband=covband; }
            void setName(const QString &name)           { this->name=name; }
            void setAngles(const QString &angles)       { this->angles=angles; }
            void setLatitude(const QString &latitude)   { this->latitude=latitude; }
            void setDisplayed(bool displayed)           { this->displayed=displayed; }
            void setId(int id)                          { this->id=id; }

            // getters
            QString getAlgorithm() const  { return algorithm; }
            QString getOutput() const     { return output; }
            QString getEncoding() const   { return encoding; }
            QString getEllipsoid() const  { return ellipsoid; }
            QString getLanguage() const   { return language; }
            QString getCovband() const    { return covband; }
            QString getName() const       { return name; }
            QString getAngles() const     { return angles; }
            QString getLatitude() const   { return latitude; }
            bool isDisplayed() const      { return displayed; }
            int getId() const             { return id; }
    }; // class AdjustmentSetting

} // namespace QGamaCore

#endif // QGAMACORE__ADJUSTMENTSETTING_H
