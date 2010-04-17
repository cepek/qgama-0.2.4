#ifndef QGAMACORE__PROJECTPROPERTIESDIALOG_H
#define QGAMACORE__PROJECTPROPERTIESDIALOG_H

#include <QDialog>

namespace Ui {
    class ProjectPropertiesDialog;
}

class ProjectPropertiesDialog : public QDialog {
    Q_OBJECT
public:
    ProjectPropertiesDialog(QWidget *parent = 0);
    ~ProjectPropertiesDialog();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::ProjectPropertiesDialog *ui;
};

#endif // QGAMACORE__PROJECTPROPERTIESDIALOG_H
