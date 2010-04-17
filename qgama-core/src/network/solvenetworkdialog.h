#ifndef SOLVENETWORKDIALOG_H
#define SOLVENETWORKDIALOG_H

#include <QDialog>

namespace Ui {
    class SolveNetworkDialog;
}

class SolveNetworkDialog : public QDialog {
    Q_OBJECT
public:
    SolveNetworkDialog(QWidget *parent = 0);
    ~SolveNetworkDialog();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::SolveNetworkDialog *ui;
};

#endif // SOLVENETWORKDIALOG_H
