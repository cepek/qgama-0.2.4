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

#ifndef QGAMACORE__PLUGININTERFACE_H
#define QGAMACORE__PLUGININTERFACE_H

#include <QtPlugin>
#include <QObject>
#include <QMap>
#include <QAction>
#include <QList>
#include <QMenu>
#include <QStringList>
#include <QIcon>

#include "../utils/applicationcomponentprovider.h"


namespace QGamaCore {

    /** General interface which every plugin has to implement.
      *
      * Specialized plugin interfaces has to be inherited from it.
      */
    class PluginInterface : public QObject
    {
    protected:
        ApplicationComponentProvider *acp;

    public:
        virtual ~PluginInterface() { }

        virtual QIcon icon() const = 0;
        virtual QString name() const = 0;
        virtual QString description() const = 0;
        virtual QStringList authors() const = 0;
        virtual QStringList items() const = 0;
        virtual QWidget* configuration() const { return 0; };

        virtual void init(ApplicationComponentProvider *acp) { this->acp = acp; }
    }; // class PluginInterface

} // namespace QGamaCore


Q_DECLARE_INTERFACE(QGamaCore::PluginInterface,"Jiri_Novak.QGamaCore.PluginInterface/1.0")


#endif // QGAMACORE__PLUGININTERFACE_H
