#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <QString>
#include <QWidget>
#include <QObject>

#include "mainwindow.h"


namespace QGamaCore {


    /**
      *
      */
    class Document : public QObject
    {
        Q_OBJECT

        public:
            Document();
            ~Document();


            bool loadFile(const QString &fileName);
            bool save();
            bool saveAs();
            bool saveFile(const QString &fileName);
            QString userFriendlyCurrentFile();
            QString currentFile() { return curFile; }
            QString documentType() { return docType; }
            virtual QString getContents() { return ""; }

        protected:
            void closeEvent(QCloseEvent *event);

        signals:
            void saveStateChanged();

        protected slots:
            void modificationChanged(bool changed);
        protected:
            virtual bool isModified() { return false; }

        private:
            bool maybeSave();
            void setCurrentFile(const QString &fileName);

            QString curFile;
            QString docType;

        protected:
            QString strippedName(const QString &fullFileName);
            MainWindow *mw;

    }; // class Document

} // namespace QGamaCore


#endif // DOCUMENT_H
