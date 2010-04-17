#ifndef QGAMACORE__DOCUMENT_H
#define QGAMACORE__DOCUMENT_H

#include <QString>
#include <QWidget>


namespace QGamaCore {

    class MainWindow;

    
    /**
      *
      */
    class Document : public QWidget
    {
        Q_OBJECT

        public:
            Document(const QString &type);
            ~Document();
            bool loadFile(const QString &fileName);
            bool save();
            bool saveAs();
            bool saveFile(const QString &fileName);
            QString userFriendlyCurrentFile();
            QString currentFile() { return curFile; }
            QString documentType() { return docType; }
            virtual QString getContent() = 0;

        signals:
            void saveStateChanged();

        protected slots:
            void modificationChanged(bool changed);

        private:
            bool maybeSave();
            void setCurrentFile(const QString &fileName);
            QString curFile;
            QString docType;

        protected:
            void closeEvent(QCloseEvent *event);
            QString strippedName(const QString &fullFileName);
            virtual void setContent(const QString &content) = 0;
            virtual bool isDocumentModified() { return false; }
            virtual void setDocumentModified(bool modified) = 0;
            virtual void initializeUi() = 0;

            MainWindow *mw;
    }; // class Document

} // namespace QGamaCore


#endif // QGAMACORE__DOCUMENT_H
