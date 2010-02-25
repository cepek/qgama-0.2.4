#ifndef XMLVALIDATIONDIALOG_H
#define XMLVALIDATIONDIALOG_H

#include <QDialog>

namespace Ui {
    class XMLValidationDialog;
}

class XMLValidationDialog : public QDialog {
    Q_OBJECT
public:
    XMLValidationDialog(QDialog *parent = 0);
    ~XMLValidationDialog();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::XMLValidationDialog *ui;
};

#endif // XMLVALIDATION_H
