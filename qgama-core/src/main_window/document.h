#ifndef QGAMACORE__DOCUMENT_H
#define QGAMACORE__DOCUMENT_H

#include <QString>
#include <QWidget>

#include "../projects_manager/project.h"


namespace QGamaCore {

    class MainWindow;

    
    /**
      *
      */
    class Document : public QWidget
    {
        Q_OBJECT

        public:
            Document(const QString &type, Project *pr);
            ~Document();
            bool loadFile(const QString &fileName);
            bool save();
            bool saveAs();
            bool saveFile(const QString &fileName);
            QString userFriendlyCurrentFile();
            QString currentFile() { return curFile; }
            QString documentType() { return docType; }
            virtual QString getContent() = 0;
            virtual void setContent(const QString &content) = 0;
            void newFile(const QString &fileName, const QString &content);
            Project* getAsociatedProject() { return project; }

        signals:
            void saveStateChanged();

        protected slots:
            void modificationChanged(bool changed);

        private:
            bool maybeSave();
            void setCurrentFile(const QString &fileName);
            QString curFile;
            QString docType;
            QGamaCore::Project *project;

        protected:
            void closeEvent(QCloseEvent *event);
            QString strippedName(const QString &fullFileName);
            virtual bool isDocumentModified() { return false; }
            virtual void setDocumentModified(bool modified) {};
            virtual void initializeUi() = 0;

            MainWindow *mw;
    }; // class Document

} // namespace QGamaCore


#endif // QGAMACORE__DOCUMENT_H
