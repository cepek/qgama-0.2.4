#ifndef QGAMACORE__HTMLVIEWER_H
#define QGAMACORE__HTMLVIEWER_H

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

#endif // QGAMACORE__HTMLVIEWER_H
