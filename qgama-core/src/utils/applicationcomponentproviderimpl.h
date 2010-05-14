#ifndef QGAMACORE__APPLICATIONCOMPONENTPROVIDERIMPL_H
#define QGAMACORE__APPLICATIONCOMPONENTPROVIDERIMPL_H

#include "applicationcomponentprovider.h"

#include <QString>
#include <QWidget>
#include <QMdiSubWindow>


namespace QGamaCore {

    // forward declarations
    class PluginsManagerDialog;
    class MainWindow;
    class ProjectsTreeWidget;
    class Document;
    class TextEditor;


    const QString OBJECT_NAME_PLUGINS_MANAGER_DIALOG = "PluginsManagerDialog";
    const QString OBJECT_NAME_MAIN_WINDOW = "MainWindow";
    const QString OBJECT_NAME_PROJECTS_TREE_WIDGET = "treeWidget_Projects";


    /**
      *
      */
    class ApplicationComponentProviderImpl : public ApplicationComponentProvider
    {
        friend class Factory;

        protected:
            static ApplicationComponentProviderImpl* instance();
            void release();

        private:
            static ApplicationComponentProviderImpl *self;
            ApplicationComponentProviderImpl() {}
            ApplicationComponentProviderImpl & operator=(ApplicationComponentProviderImpl&);
            ApplicationComponentProviderImpl(const ApplicationComponentProviderImpl&);
            ~ApplicationComponentProviderImpl();
            static int pointersCount;

            QWidget* findTopLevelWidget(const QString &name);
            QWidget* findWidget(const QString &name);

        public:
            virtual QMdiSubWindow* getMdiSubWindow(const QString &file);

            virtual PluginsManagerDialog* getPluginsManagerDialog();
            virtual MainWindow* getMainWindow();
            virtual ProjectsTreeWidget* getProjectsTreeWidget();
            virtual Document* getActiveDocument();
            virtual TextEditor* getActiveTextEditor();
    };
}


#endif // APPLICATIONCOMPONENTPROVIDERIMPL_H
