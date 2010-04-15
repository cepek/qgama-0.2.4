#include "projectpropertiesdialog.h"
#include "ui_projectpropertiesdialog.h"


/**
  *
  */
ProjectPropertiesDialog::ProjectPropertiesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProjectPropertiesDialog)
{
    ui->setupUi(this);
}


/**
  *
  */
ProjectPropertiesDialog::~ProjectPropertiesDialog()
{
    delete ui;
}


/**
  *
  */
void ProjectPropertiesDialog::changeEvent(QEvent *e)
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
