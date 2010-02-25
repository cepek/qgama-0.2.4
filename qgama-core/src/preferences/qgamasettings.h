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

#ifndef QGAMASETTINGS_H
#define QGAMASETTINGS_H

#include <QMap>
#include <QString>
#include <QVariant>


namespace QGamaCore {

    /** Abstract class for handling application settings.
      *
      */
    class QGamaSettings
    {
        protected:
            /// Inner map to hold the settings at runtime.
            QMap<QString,QVariant> settings;

        public:
            /** Gets the value corresponding to the specified key from the inner map.
              *
              * @param[in]  key     The name of the key.
              * @return             The value corresponding to the requested key.
              */
            QVariant get(const QString &key) { return settings.value(key); }

            /** Sets the value corresponding to the specified key from the inner map.
              *
              * @param[in]  key     The name of the key.
              * @param[in]  value   The value corresponding to the requested key.
              */
            void set(const QString &key, const QVariant &value) { settings.insert(key,value); }

            /** Removes the value corresponding to the specified key from the inner map.
              *
              * @param[in]  key     The name of the key.
              */
            void del(const QString &key) { settings.remove(key); }

            virtual void loadValue(const QString &key) = 0;
            virtual void saveValue(const QString &key) = 0;
            virtual void removeValue(const QString &key) = 0;

            virtual void loadAll() = 0;
            virtual void saveAll() = 0;
            virtual void removeAll() = 0;
    }; // class

} // namespace


#endif // QGAMASETTINGS_H
