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

#include <QString>
#include <QFileDialog>
#include <QTreeWidgetItem>
#include <iostream>

#include "pluginsmanagerdialog.h"
#include "pluginsmanagerimpl.h"
#include "../preferences/settingsimpl.h"
#include "../plugins_manager/plugininterface.h"
#include "../utils/utils.h"

using namespace QGamaCore;


PluginsManagerDialog::PluginsManagerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new QGamaCore::Ui::PluginsManagerDialog),
    pm(PluginsManagerImpl::instance()),
    settings(SettingsImpl::instance())
{
    ui->setupUi(this);

    ui->lineEdit_PluginDirectoryValue->setText(settings.get("plugins/directory").toString());

    ui->treeWidget_Plugins->sortByColumn(1);
    ui->treeWidget_Plugins->sortItems(1,Qt::AscendingOrder);
}


PluginsManagerDialog::~PluginsManagerDialog()
{
    delete ui;
}


void PluginsManagerDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}


void PluginsManagerDialog::addLoadedPlugin(const QString &name, int status, PluginInterface* plugin)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeWidget_Plugins);
    item->setCheckState(0,Qt::Checked);
    status==Enabled ? item->setCheckState(0,Qt::Checked) : item->setCheckState(0,Qt::Unchecked);
    item->setIcon(1,plugin->icon());
    item->setText(1,plugin->name());

    QString overview;
    QStringList authors = plugin->authors();
    overview.append("<h3>"+plugin->name()+"</h3><h4>Authors:</h4>");
    overview.append("<p>");
    for (int i=0; i<authors.size(); ++i) {
        overview.append(authors[i]);
        if (i!=authors.size()-1)
            overview.append(",<br/>");
    }
    overview.append("</p>");
    overview.append("<p><h4>Description:</h4>");
    overview.append(plugin->description());
    overview.append("</p>");

    item->setText(2,overview);
    item->setText(3,name);
}


void PluginsManagerDialog::on_toolButton_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if (!dir.isEmpty()) {
        ui->lineEdit_PluginDirectoryValue->setText(dir);
        settings.set("plugins/directory",dir);
    }
}


void PluginsManagerDialog::on_buttonBox_accepted()
{  
    QStringList enabledPlugins;
    QStringList disabledPlugins;

    QTreeWidgetItem *item = 0;
    for (int i=0; i<ui->treeWidget_Plugins->topLevelItemCount(); ++i) {
         item = ui->treeWidget_Plugins->topLevelItem(i);
         if (item->checkState(0) == Qt::Checked)
             enabledPlugins.append(item->text(3));
         else
             disabledPlugins.append(item->text(3));
    }

    if (!enabledPlugins.isEmpty()) {
        settings.set("plugins/enabledPlugins",enabledPlugins);
        settings.saveValue("plugins/enabledPlugins");
    }
    else {
        settings.del("plugins/enabledPlugins");
        settings.removeValue("plugins/enabledPlugins");
    }

    settings.saveValue("plugins/directory");

    for (QStringList::iterator i=disabledPlugins.begin(); i!=disabledPlugins.end(); ++i) {
        pm.unloadPlugin(*i);
    }

    for (QStringList::iterator i=enabledPlugins.begin(); i!=enabledPlugins.end(); ++i) {
        pm.loadPlugin(*i);
    }
}


void PluginsManagerDialog::on_treeWidget_Plugins_currentItemChanged(QTreeWidgetItem* current, QTreeWidgetItem* previous)
{
    ui->textEdit_Description->setText(current->text(2));

    PluginInterface *plugin = pm.plugin(current->text(3));
    if (ui->tabWidget->findChild<QWidget*>(tr("Configuration")) != 0)
        ui->tabWidget->removeTab(1);
    ui->tabWidget->addTab(plugin->configuration(),tr("Configuration"));
}
