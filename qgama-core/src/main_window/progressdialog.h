#ifndef QGAMACORE__PROGRESSDIALOG_H
#define QGAMACORE__PROGRESSDIALOG_H

#include <QProgressDialog>
#include <QWidget>


namespace QGamaCore {

    /**
      *
      */
    class ProgressDialog : public QProgressDialog
    {
        Q_OBJECT

        public:
            ProgressDialog(QWidget *parent, const QString &title, int minimum, int maximum) : QProgressDialog(parent) {
                setRange(minimum, maximum);
                setCancelButton(0);
                setAttribute(Qt::WA_DeleteOnClose);
                setWindowTitle(title);
                show();
            }

        private slots:
            void setLabel(int value, const QString &text) { setValue(value); setLabelText(text); }
    }; // class ProgressDialog

} // namespace QGamaCore


#endif // QGAMACORE__PROGRESSDIALOG_H
