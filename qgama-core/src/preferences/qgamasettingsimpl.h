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

#ifndef QGAMASETTINGSIMPL_H
#define QGAMASETTINGSIMPL_H

#include <QMap>
#include <QSettings>
#include <QVariant>

#include "qgamasettings.h"


namespace QGamaCore {

    /** Implementation of QGamaCore::QGamaSettings class.
      *
      * Utilize QSettings for storing key/value pairs. It's implemented as Singleton.
      */
    class QGamaSettingsImpl : public QGamaSettings
    {
        private:
            /// Pointer to the QGamaCore::QGamaSettingsImpl object.
            static QGamaSettingsImpl *self;                     // singleton
            QGamaSettingsImpl();                                // forbidden
            /// Private operator= (singleton implementation).
            QGamaSettingsImpl& operator=(QGamaSettingsImpl&);   // forbidden
            /// Private copy constructor (singleton implementation)
            QGamaSettingsImpl(const QGamaSettingsImpl&);        // forbidden

            /// QSettings object used for storing persistent settings.
            QSettings applicationSettings;                      // QSettings used for storing values

        public:
            /** Method returning a pointer to QGamaCore::PluginManagerImpl object.
              *
              * On the first call the instance is created, sequentially pointers to this instance are returned.
              */
            static QGamaSettingsImpl& instance() {
                if (self == 0)
                    self = new QGamaSettingsImpl();
                return *self;
            }

            ~QGamaSettingsImpl();

            void saveValue(const QString &key);
            void loadValue(const QString &key);
            void removeValue(const QString &key);

            void saveAll();
            void loadAll();
            void removeAll();
    }; // class QGamaSettingsImpl

} // namespace QGamaCore


#endif // QGAMASETTINGSIMPL_H
