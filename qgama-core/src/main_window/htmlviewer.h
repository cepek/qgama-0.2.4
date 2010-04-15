#ifndef HTMLVIEWER_H
#define HTMLVIEWER_H

#include <QWebView>
#include <QString>


namespace QGamaCore {

    /**
      *
      */
    class HtmlViewer : public QWebView
    {
        public:
            HtmlViewer(const QString &type);
            ~HtmlViewer();
            //bool loadFile(const QString &fileName);

        private:
            //QString curFile();
            //QString docType();
    }; // class HtmlViewer

} // namespace

#endif // HTMLVIEWER_H
