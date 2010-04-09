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

#ifndef PLUGINSMANAGERDIALOG_H
#define PLUGINSMANAGERDIALOG_H

#include <QDialog>
#include <QMap>
#include <QWidget>
#include <QString>

#include <ui_pluginsmanagerdialog.h>
#include "../preferences/settings.h"
#include "../plugins_manager/plugininterface.h"
#include "../plugins_manager/pluginsmanager.h"


namespace QGamaCore {

    /** Class generated from Qt Designer's .ui file.
      *
      * It defines the appearence of QGamaCore::PluginsManagerDialog.
      */
    namespace Ui {
        class PluginsManagerDialog : public Ui_PluginsManagerDialog {};

    } // namespace Ui


    /** PluginManagerDialog implementation class.
      *
      * All the underlaying functionality for QGamaCore::Ui::PluginsManagerDialog.
      */
    class PluginsManagerDialog : public QDialog
    {
        Q_OBJECT

        public:
            PluginsManagerDialog(QWidget *parent = 0);
            ~PluginsManagerDialog();
            void addLoadedPlugin(const QString &name, int status, QGamaCore::PluginInterface* plugin);

        protected:
            void changeEvent(QEvent *e);

        private:
            QGamaCore::Ui::PluginsManagerDialog *ui;
            QGamaCore::PluginsManager *pm;
            QGamaCore::Settings *settings;

        private slots:
            void on_treeWidget_Plugins_currentItemChanged(QTreeWidgetItem* current, QTreeWidgetItem* previous);
            void on_buttonBox_accepted();
            void on_toolButton_clicked();
    }; // class PluginsManagerDialog

} // namespace QGamaCore


#endif // PLUGINSMANAGERDIALOG_H
