#include "xmlvalidationdialog.h"
#include "ui_xmlvalidationdialog.h"

XMLValidationDialog::XMLValidationDialog(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::XMLValidationDialog)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/images/icons/babieca-64.png"));
}

XMLValidationDialog::~XMLValidationDialog()
{
    delete ui;
}

void XMLValidationDialog::changeEvent(QEvent *e)
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
