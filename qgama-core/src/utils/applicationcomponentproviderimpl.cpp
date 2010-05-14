#include <QtGui>

#include "applicationcomponentproviderimpl.h"
#include "../plugins_manager/pluginsmanagerdialog.h"
#include "../projects_manager/projectstreewidget.h"
#include "../main_window/mainwindow.h"
#include "../main_window/document.h"
#include "../main_window/texteditor.h"

using namespace QGamaCore;

// Inicialization of the private instance pointer to null.
ApplicationComponentProviderImpl* ApplicationComponentProviderImpl::self = 0;

// inicialization of the private counter of pointers
int ApplicationComponentProviderImpl::pointersCount = 0;


/* ===============================================================================================================*/
/**
  *
  */
ApplicationComponentProviderImpl::~ApplicationComponentProviderImpl() {
    qDebug() << "ApplicationComponentProviderImpl destructor";
}


/* ===============================================================================================================*/
/**
  *
  */
ApplicationComponentProviderImpl* ApplicationComponentProviderImpl::instance() {
    if (self == 0) {
        self = new ApplicationComponentProviderImpl();
    }
    pointersCount++;

    qDebug() << "ApplicationComponentProviderImpl instance created, total: " << pointersCount;

    return self;
}


/* ===============================================================================================================*/
/**
  *
  */
void ApplicationComponentProviderImpl::release()
{
    pointersCount--;

    if (pointersCount == 0) {
      delete self;
      self = 0;
    }

    qDebug() << "ApplicationComponentProviderImpl instance released, total: " << pointersCount;
}


/* ===============================================================================================================*/
/**
  *
  */
QWidget* ApplicationComponentProviderImpl::findTopLevelWidget(const QString &name)
{
    // get the list of active top-level widgets
    QList<QWidget*> windows = qApp->topLevelWidgets();
    // find the first one corresponding to the specified object name and return it's pointer if found
    for (QList<QWidget*>::iterator i=windows.begin(); i!=windows.end(); ++i) {
        if ((*i)->objectName()==name) {
            return *i;
        }
    }

    // otherwise return null
    return 0;
}


/* ===============================================================================================================*/
/**
  *
  */
QWidget* ApplicationComponentProviderImpl::findWidget(const QString &name)
{
    // get the list of active top-level widgets
    QList<QWidget*> windows = qApp->allWidgets();
    // find the first one corresponding to the specified object name and return it's pointer if found
    for (QList<QWidget*>::iterator i=windows.begin(); i!=windows.end(); ++i) {
        if ((*i)->objectName()==name) {
            return *i;
        }
    }

    // otherwise return null
    return 0;
}


/* ===============================================================================================================*/
/**
  *
  */
QMdiSubWindow* ApplicationComponentProviderImpl::getMdiSubWindow(const QString &file)
{
    // get the cannonical file path
    QString filePath = QFileInfo(file).canonicalFilePath();

    // get the list of all active subwindows of mdiArea
    QMdiArea *mdiArea = qobject_cast<QMdiArea*> (findWidget("mdiArea"));
    QList<QMdiSubWindow*> subWindows = mdiArea->subWindowList();

    // iterate through subwindows list, find the corresponding file
    for (QList<QMdiSubWindow*>::iterator i=subWindows.begin(); i!=subWindows.end(); ++i) {
        Document *document = qobject_cast<Document*> ((*i)->widget());
        // if exists, return its pointer
        if (document->currentFile() == filePath)
            return *i;
    }

    // otherwise return null
    return 0;
}


/* ===============================================================================================================*/
/**
  *
  */
PluginsManagerDialog* ApplicationComponentProviderImpl::getPluginsManagerDialog()
{
    return qobject_cast<PluginsManagerDialog*> (findTopLevelWidget(OBJECT_NAME_PLUGINS_MANAGER_DIALOG));
}


/* ===============================================================================================================*/
/**
  *
  */
MainWindow* ApplicationComponentProviderImpl::getMainWindow()
{
    return qobject_cast<MainWindow*> (findTopLevelWidget(OBJECT_NAME_MAIN_WINDOW));
}


/* ===============================================================================================================*/
/**
  *
  */
ProjectsTreeWidget* ApplicationComponentProviderImpl::getProjectsTreeWidget()
{
    return qobject_cast<ProjectsTreeWidget*> (findWidget(OBJECT_NAME_PROJECTS_TREE_WIDGET));
}


/* ===============================================================================================================*/
/**
  *
  */
Document* ApplicationComponentProviderImpl::getActiveDocument()
{
    MainWindow* mw = getMainWindow();
    Q_ASSERT(mw!=0 && "mainWindow pointer is 0!");

    Document *document = mw->getActiveDocument();
    Q_ASSERT(document!=0 && "document pointer is 0!");

    return document;
}


/* ===============================================================================================================*/
/**
  *
  */
TextEditor* ApplicationComponentProviderImpl::getActiveTextEditor()
{
    Document* document = getActiveDocument();
    TextEditor* textEditor = qobject_cast<TextEditor*>(document);
    Q_ASSERT(textEditor!=0 && "textEditor pointer is 0!");
    return textEditor;
}
