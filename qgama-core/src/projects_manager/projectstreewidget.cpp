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

#include <QWidget>
#include <QContextMenuEvent>
#include <QAction>
#include <QCursor>
#include <QMenu>
#include <QTreeWidgetItem>

#include "projectstreewidget.h"
#include "../utils/utils.h"
#include "../main_window/mainwindow.h"

#include <iostream>

using namespace QGamaCore;


/**
  *
  */
ProjectsTreeWidget::ProjectsTreeWidget(QWidget *parent) : QTreeWidget(parent)
{
    connect(this, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(openFileDoubleClick(QTreeWidgetItem*,int)));
    connect(this, SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)), this, SLOT(changeActiveProject(QTreeWidgetItem*,QTreeWidgetItem*)));

    MainWindow *mw = qobject_cast<MainWindow*> (Utils::findTopLevelWidget("MainWindow"));
    connect(this, SIGNAL(openFile(QString)), mw, SLOT(openFile(QString)));

    this->setSortingEnabled(true);
    this->sortByColumn(0);
    this->sortItems(0,Qt::AscendingOrder);
}


/**
  *
  */
void ProjectsTreeWidget::contextMenuEvent(QContextMenuEvent *event)
{
    if (itemAt(event->pos())->text(1) == "projectFile") {
        QMenu menu(this);
        QAction *action_Open = menu.addAction(tr("Open File"));
        action_Open->setData(itemAt(event->pos())->parent()->text(2)+"/"+itemAt(event->pos())->parent()->text(0)+"/"+itemAt(event->pos())->text(0));
        connect(&menu, SIGNAL(triggered(QAction*)), this, SLOT(openFileContextMenu(QAction*)));
        menu.exec(event->globalPos());
    }
}


/**
  *
  */
void ProjectsTreeWidget::openFileDoubleClick(QTreeWidgetItem *current, int column)
{
    if (current->text(1) == "projectFile") {
        emit openFile(current->parent()->text(2)+"/"+current->parent()->text(0)+"/"+current->text(0));
    }
}


/**
  *
  */
void ProjectsTreeWidget::openFileContextMenu(QAction *action)
{
    emit openFile(action->data().toString());
}


/**
  *
  */
void ProjectsTreeWidget::changeActiveProject(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    for (int i=0; i<topLevelItemCount(); ++i) {
         topLevelItem(i)->setSelected(false);
         if (topLevelItem(i)->childCount() != 0) {
             for (int j=0; j<topLevelItem(i)->childCount(); ++j) {
                 topLevelItem(i)->child(j)->setSelected(false);
             }
         }
    }

    if (current->text(1) == "projectName") {
        current->setSelected(true);
        QMenu *menuFile = qobject_cast<QMenu*> (Utils::findWidget("menu_File"));

        QList<QAction*> actions = menuFile->actions();
        for (QList<QAction*>::iterator i=actions.begin(); i!=actions.end(); ++i) {
            if ((*i)->objectName() == "action_Close_Project" || (*i)->objectName() == "action_Project_Properties") {
                QString text = (*i)->text();
                text = text.left(text.indexOf("(")).trimmed();
                (*i)->setText(text+" ("+current->text(0)+")");
            }
        }
    }

    else if (current->parent()->text(1) == "projectName") {
        current->parent()->setSelected(true);
        QMenu *menuFile = qobject_cast<QMenu*> (Utils::findWidget("menu_File"));

        QList<QAction*> actions = menuFile->actions();
        for (QList<QAction*>::iterator i=actions.begin(); i!=actions.end(); ++i) {
            if ((*i)->objectName() == "action_Close_Project" || (*i)->objectName() == "action_Project_Properties") {
                QString text = (*i)->text();
                text = text.left(text.indexOf("(")).trimmed();
                (*i)->setText(text+" ("+current->parent()->text(0)+")");
            }
        }
    }
}
