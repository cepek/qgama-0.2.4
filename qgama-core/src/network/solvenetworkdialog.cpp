#include "solvenetworkdialog.h"
#include "ui_solvenetworkdialog.h"

SolveNetworkDialog::SolveNetworkDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SolveNetworkDialog)
{
    ui->setupUi(this);
}

SolveNetworkDialog::~SolveNetworkDialog()
{
    delete ui;
}

void SolveNetworkDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
