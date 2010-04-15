#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <QString>
#include <QWidget>
#include <QObject>


namespace QGamaCore {

    class MainWindow;


    /**
      *
      */
    class Document : public QObject
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
            virtual QWidget* getWidget() = 0;

        signals:
            void saveStateChanged();

        public slots:
            void showMaximized() { getWidget()->showMaximized(); }
            void close() { getWidget()->close(); }

        protected slots:
            void modificationChanged(bool changed);

        private:
            bool maybeSave();

            void setCurrentFile(const QString &fileName);

            QString curFile;
            QString docType;

        protected:
            void closeEvent(QCloseEvent *event);

            virtual bool isModified() { return false; }

            QString strippedName(const QString &fullFileName);

            virtual void setContent(const QString &content) = 0;

            MainWindow *mw;
    }; // class Document

} // namespace QGamaCore


#endif // DOCUMENT_H
