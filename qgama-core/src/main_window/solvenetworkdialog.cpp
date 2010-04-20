#include <QtGui>

#include "solvenetworkdialog.h"
#include "../utils/applicationcomponentprovider.h"
#include "../projects_manager/adjustmentsetting.h"
#include "mainwindow.h"
#include "../adjustment/solvenetwork.h"
#include "progressdialog.h"


using namespace QGamaCore;


enum { AdjustmentSettingId=32 };


/**
  *
  */
SolveNetworkDialog::SolveNetworkDialog(QWidget *parent) :
    QDialog(parent),
    ui(new QGamaCore::Ui::SolveNetworkDialog),
    mw(ApplicationComponentProvider::getMainWindow())
{
    ui->setupUi(this);

    Q_ASSERT(mw!=0 && "mainWindow pointer is 0!");

    document = mw->getActiveDocument();

    Q_ASSERT(document!=0 && "document pointer is 0!");

    project = document->getAsociatedProject();

    Q_ASSERT(project!=0 && "project pointer is 0!");

    // initialize Ui
    initializeUi();
}


/**
  *
  */
void SolveNetworkDialog::initializeUi()
{
    // fill the settings combobox
    QList<AdjustmentSetting> &adjustmentSettings = project->getAdjustmentSettings();
    for (int i=0; i<adjustmentSettings.size(); i++) {
        AdjustmentSetting &as = adjustmentSettings[i];
        ui->comboBox_Adjustment_Setting->addItem(as.getName());
        ui->comboBox_Adjustment_Setting->setItemData(i,as.getId(),AdjustmentSettingId);
    }

    // set the network name
    ui->lineEdit_Network->setText(document->userFriendlyCurrentFile());
    ui->lineEdit_Network->setReadOnly(true);
}


/**
  *
  */
SolveNetworkDialog::~SolveNetworkDialog()
{
    delete ui;
}


/**
  *
  */
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


/**
  *
  */
void SolveNetworkDialog::accept()
{
    this->hide();

    // declare streams
    QString inputXmlStream = document->getContent();

    // get the selected adjustment setting
    int itemIndex = ui->comboBox_Adjustment_Setting->currentIndex();
    int index = ui->comboBox_Adjustment_Setting->itemData(itemIndex, AdjustmentSettingId).toInt();
    AdjustmentSetting *as = project->getAdjustmentSetting(index);

    // start the adjustment in the separate thread
    SolveNetwork *solver = new SolveNetwork(inputXmlStream, as, document);
    connect(solver, SIGNAL(solved(QString,QString,Document*,AdjustmentSetting*)), mw, SLOT(onAdjustmentSuccess(QString,QString,Document*,AdjustmentSetting*)));
    connect(solver, SIGNAL(solvingFailed(QString)), mw, SLOT(onAdjustmentFailure(QString)));

    // dissable solve network action and add progress bar
    ProgressDialog *progressDialog = new ProgressDialog(document,tr("Adjustment in progress..."),0,11);

    connect(solver, SIGNAL(solved(QString,QString,Document*,AdjustmentSetting*)), progressDialog, SLOT(close()));
    connect(solver, SIGNAL(solvingFailed(QString)), progressDialog, SLOT(close()));
    connect(solver, SIGNAL(label(int,QString)), progressDialog, SLOT(setLabel(int,QString)));
    connect(this, SIGNAL(setCalculating(bool)), mw, SLOT(setCalculating(bool)));
    emit setCalculating(true);

    solver->start();

    done(Accepted);
}
