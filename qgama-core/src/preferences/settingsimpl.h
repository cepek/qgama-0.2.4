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

#ifndef QGAMACORE__SETTINGSIMPL_H
#define QGAMACORE__SETTINGSIMPL_H

#include <QMap>
#include <QSettings>
#include <QVariant>

#include "settings.h"


namespace QGamaCore {

    /** Implementation of QGamaCore::QGamaSettings class.
      *
      * Utilize QSettings for storing key/value pairs. It's implemented as Singleton.
      */
    class SettingsImpl : public Settings
    {
        friend class Factory;

        private:

            /// Pointer to the QGamaCore::QGamaSettingsImpl object.
            static SettingsImpl *self;                     // singleton

            SettingsImpl();                                // forbidden

            /// Private operator= (singleton implementation).
            SettingsImpl& operator=(SettingsImpl&);        // forbidden

            /// Private copy constructor (singleton implementation)
            SettingsImpl(const SettingsImpl&);             // forbidden

            ~SettingsImpl();                               // forbidden

            /// QSettings object used for storing persistent settings.
            QSettings applicationSettings;                 // QSettings used for storing values

            /// Counter of the active pointers.
            static int pointersCount;

        protected:

            void saveValue(const QString &key);
            void loadValue(const QString &key);

            void saveAll();
            void loadAll();

            static SettingsImpl* instance();
            void release();
    }; // class SettingsImpl

} // namespace QGamaCore


#endif // QGAMACORE__QGAMASETTINGSIMPL_H
