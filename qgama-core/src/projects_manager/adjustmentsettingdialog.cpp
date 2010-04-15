#include <QtGui>
#include <iostream>

#include "adjustmentsettingdialog.h"
#include "../factory.h"
#include "project.h"
#include "adjustmentsetting.h"

using namespace QGamaCore;


/**
  *
  */
AdjustmentSettingDialog::AdjustmentSettingDialog(AdjustmentSetting *as, QWidget *parent) :
    QDialog(parent),
    ui(new QGamaCore::Ui::AdjustmentSettingDialog),
    prm(Factory::getProjectsManager()),
    as(as)
{
    // setup ui
    ui->setupUi(this);

    if (as!=0) {
        // set mode
        mode = "Edit";

        // set titles
        setWindowTitle(tr("Edit Adjustment Setting"));
        ui->groupBox_Adjustment_Setting->setTitle(tr("Edit Adjustment Setting"));

        // set options from adjustmentsetting
        ui->comboBox_Algorithm->setCurrentIndex(ui->comboBox_Algorithm->findText(as->getAlgorithm()));
        ui->comboBox_Angles->setCurrentIndex(ui->comboBox_Angles->findText(as->getAngles()));
        ui->spinBox_Covband->setValue(as->getCovband().toInt());
        if (!as->getLatitude().isEmpty() && !as->getEllipsoid().isEmpty()) {
            ui->checkBox_Apply_Corrections->setChecked(true);
            ui->comboBox_Ellipsoid->setCurrentIndex(ui->comboBox_Ellipsoid->findText(as->getEllipsoid()));
            ui->lineEdit_Latitude->setText(as->getLatitude());
        }
        else {
            ui->comboBox_Ellipsoid->setCurrentIndex(ui->comboBox_Ellipsoid->findText("wgs84"));
            if (ui->comboBox_Angles->currentText()=="400")
                ui->lineEdit_Latitude->setText("50");
            else
                ui->lineEdit_Latitude->setText("40");
        }
        ui->comboBox_Encoding->setCurrentIndex(ui->comboBox_Encoding->findText(as->getEncoding()));
        ui->comboBox_Language->setCurrentIndex(ui->comboBox_Language->findText(as->getLanguage()));
        ui->lineEdit_Name->setText(as->getName());
        std::cout << as->getOutput().toStdString() << std::endl;
        bool html = as->getOutput().contains("html");
        bool xml  = as->getOutput().contains("xml");
        bool txt  = as->getOutput().contains("txt");
        ui->checkBox_HTML->setChecked(html);
        ui->checkBox_TXT->setChecked(txt);
        ui->checkBox_XML->setChecked(xml);
    }
    else {
        // set mode
        mode = "Create";

        // set titles
        setWindowTitle(tr("Create New Adjustment Setting"));
        ui->groupBox_Adjustment_Setting->setTitle(tr("Create New Adjustment Setting"));

        // set options from adjustmentsetting
        ui->comboBox_Algorithm->setCurrentIndex(ui->comboBox_Algorithm->findText("svd"));
        ui->comboBox_Angles->setCurrentIndex(ui->comboBox_Angles->findText("400"));
        ui->spinBox_Covband->setValue(-1);
        ui->checkBox_Apply_Corrections->setChecked(false);
        ui->comboBox_Ellipsoid->setCurrentIndex(ui->comboBox_Ellipsoid->findText("wgs84"));
        ui->lineEdit_Latitude->setText("50");
        ui->comboBox_Encoding->setCurrentIndex(ui->comboBox_Encoding->findText("utf-8"));
        ui->comboBox_Language->setCurrentIndex(ui->comboBox_Language->findText("en"));
        ui->lineEdit_Name->setText(tr("NewAdjustmentSetting"));
        ui->checkBox_HTML->setChecked(true);
        ui->checkBox_TXT->setChecked(true);
        ui->checkBox_XML->setChecked(true);
    }

    // make connections
    connect(ui->buttonBox, SIGNAL(helpRequested()), this, SLOT(showHelp()));
}


/**
  *
  */
AdjustmentSettingDialog::~AdjustmentSettingDialog()
{
    Factory::releaseProjectsManager(prm);

    delete ui;
}


/**
  *
  */
void AdjustmentSettingDialog::changeEvent(QEvent *e)
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


/**
  *
  */
void AdjustmentSettingDialog::on_checkBox_Apply_Corrections_toggled(bool checked)
{
    if (checked) {
        ui->comboBox_Ellipsoid->setEnabled(true);
        ui->lineEdit_Latitude->setEnabled(true);
        ui->label_Ellipsoid->setEnabled(true);
        ui->label_Latitude->setEnabled(true);
    }
    else {
        ui->comboBox_Ellipsoid->setEnabled(false);
        ui->lineEdit_Latitude->setEnabled(false);
        ui->label_Ellipsoid->setEnabled(false);
        ui->label_Latitude->setEnabled(false);
    }
}


/**
  *
  */
void AdjustmentSettingDialog::on_lineEdit_Name_textChanged(QString text)
{
    bool found = false;
    QList<AdjustmentSetting>& adjustmentSettings = prm->getActiveProject()->getAdjustmentSettings();
    for (int i=0; i<adjustmentSettings.size(); i++) {
        if (text == adjustmentSettings[i].getName()) {
            if ((mode == "Edit" && text!=as->getName()) || (mode == "Create")) {
                ui->label_Warning->setVisible(true);
                    ui->label_Warning_Icon->setVisible(true);
                    ui->label_Warning->setText(tr("Adjustment setting with the specified name already exists! Choose diferent one."));
                    found = true;
                    break;
            }
        }
        if (!found) {
            ui->label_Warning->setVisible(false);
            ui->label_Warning_Icon->setVisible(false);
        }
    }
}


/**
  *
  */
void AdjustmentSettingDialog::showHelp()
{
    QString message = tr("Specify the parameters for the new adjustment setting!");

    if (mode == "Edit")
        QMessageBox::information(this, tr("Edit Adjustment Setting Dialog Help"), message);
    else
        QMessageBox::information(this, tr("Create New Adjustment Setting Dialog Help"), message);
}


/**
  *
  */
void AdjustmentSettingDialog::accept()
{
    if (mode == "Create") {
        AdjustmentSetting adjSet;
        as = &adjSet;
        as->setId(prm->getActiveProject()->getNextSettingsId());
    }

    // save the values from dialog
    as->setAlgorithm(ui->comboBox_Algorithm->currentText());
    as->setAngles(ui->comboBox_Angles->currentText());
    as->setCovband(QString::number(ui->spinBox_Covband->value()));
    as->setEncoding(ui->comboBox_Encoding->currentText());
    as->setLanguage(ui->comboBox_Language->currentText());
    if (ui->checkBox_Apply_Corrections->isChecked()) {
        as->setLatitude(ui->lineEdit_Latitude->text());
        as->setEllipsoid(ui->comboBox_Ellipsoid->currentText());
    }
    else {
        as->setLatitude("");
        as->setEllipsoid("");
    }
    as->setName(ui->lineEdit_Name->text());
    QString output;
    if (ui->checkBox_HTML->isChecked())
        output+="html|";
    if (ui->checkBox_TXT->isChecked())
        output+="txt|";
    if (ui->checkBox_XML->isChecked())
        output+="xml|";
    output=output.left(output.size()-1);
    as->setOutput(output);

    if (mode == "Create") {
        prm->getActiveProject()->newAdjustmentSetting(*as);
    }

    // accept dialog
    done(Accepted);
}
