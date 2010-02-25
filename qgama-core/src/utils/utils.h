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

#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <QWidget>


namespace QGamaCore {

    /// Auxiliary enumeration.
    enum { Enabled, NotEnabled };

    /** Class containing static methods used all over the rest of the application.
      *
      */
    class Utils
    {
        private:
            Utils(); // forbidden (class contains only static methods)

        public:
            static QWidget* findTopLevelWidget(const QString &name);
    }; // class Utils

} // namespace QGamaCore


#endif // UTILS_H
