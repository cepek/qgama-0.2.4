/********************************************************************************
** Form generated from reading UI file 'pluginsmanagerdialog.ui'
**
** Created: Wed Mar 24 17:00:34 2010
**      by: Qt User Interface Compiler version 4.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLUGINSMANAGERDIALOG_H
#define UI_PLUGINSMANAGERDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QTabWidget>
#include <QtGui/QTextEdit>
#include <QtGui/QToolButton>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PluginsManagerDialog
{
public:
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout;
    QLabel *label_Title;
    QTreeWidget *treeWidget_Plugins;
    QLabel *label_Filter;
    QLineEdit *lineEdit_FilterValue;
    QLabel *label_PluginDirectory;
    QLineEdit *lineEdit_PluginDirectoryValue;
    QToolButton *toolButton;
    QDialogButtonBox *buttonBox;
    QTabWidget *tabWidget;
    QWidget *tab_Overview;
    QVBoxLayout *verticalLayout;
    QTextEdit *textEdit_Description;

    void setupUi(QDialog *PluginsManagerDialog)
    {
        if (PluginsManagerDialog->objectName().isEmpty())
            PluginsManagerDialog->setObjectName(QString::fromUtf8("PluginsManagerDialog"));
        PluginsManagerDialog->setWindowModality(Qt::ApplicationModal);
        PluginsManagerDialog->resize(599, 366);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(PluginsManagerDialog->sizePolicy().hasHeightForWidth());
        PluginsManagerDialog->setSizePolicy(sizePolicy);
        PluginsManagerDialog->setModal(true);
        horizontalLayout = new QHBoxLayout(PluginsManagerDialog);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_Title = new QLabel(PluginsManagerDialog);
        label_Title->setObjectName(QString::fromUtf8("label_Title"));
        label_Title->setWordWrap(true);

        gridLayout->addWidget(label_Title, 0, 0, 1, 3);

        treeWidget_Plugins = new QTreeWidget(PluginsManagerDialog);
        treeWidget_Plugins->setObjectName(QString::fromUtf8("treeWidget_Plugins"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(1);
        sizePolicy1.setHeightForWidth(treeWidget_Plugins->sizePolicy().hasHeightForWidth());
        treeWidget_Plugins->setSizePolicy(sizePolicy1);
        treeWidget_Plugins->setProperty("showDropIndicator", QVariant(true));
        treeWidget_Plugins->setAlternatingRowColors(false);
        treeWidget_Plugins->setItemsExpandable(true);
        treeWidget_Plugins->setSortingEnabled(true);
        treeWidget_Plugins->setAnimated(false);
        treeWidget_Plugins->setAllColumnsShowFocus(true);
        treeWidget_Plugins->header()->setCascadingSectionResizes(false);
        treeWidget_Plugins->header()->setDefaultSectionSize(100);
        treeWidget_Plugins->header()->setHighlightSections(false);
        treeWidget_Plugins->header()->setMinimumSectionSize(27);
        treeWidget_Plugins->header()->setProperty("showSortIndicator", QVariant(true));
        treeWidget_Plugins->header()->setStretchLastSection(true);

        gridLayout->addWidget(treeWidget_Plugins, 1, 0, 1, 3);

        label_Filter = new QLabel(PluginsManagerDialog);
        label_Filter->setObjectName(QString::fromUtf8("label_Filter"));

        gridLayout->addWidget(label_Filter, 2, 0, 1, 1);

        lineEdit_FilterValue = new QLineEdit(PluginsManagerDialog);
        lineEdit_FilterValue->setObjectName(QString::fromUtf8("lineEdit_FilterValue"));
        QSizePolicy sizePolicy2(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(lineEdit_FilterValue->sizePolicy().hasHeightForWidth());
        lineEdit_FilterValue->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(lineEdit_FilterValue, 2, 1, 1, 2);

        label_PluginDirectory = new QLabel(PluginsManagerDialog);
        label_PluginDirectory->setObjectName(QString::fromUtf8("label_PluginDirectory"));

        gridLayout->addWidget(label_PluginDirectory, 3, 0, 1, 1);

        lineEdit_PluginDirectoryValue = new QLineEdit(PluginsManagerDialog);
        lineEdit_PluginDirectoryValue->setObjectName(QString::fromUtf8("lineEdit_PluginDirectoryValue"));
        sizePolicy2.setHeightForWidth(lineEdit_PluginDirectoryValue->sizePolicy().hasHeightForWidth());
        lineEdit_PluginDirectoryValue->setSizePolicy(sizePolicy2);
        lineEdit_PluginDirectoryValue->setReadOnly(true);

        gridLayout->addWidget(lineEdit_PluginDirectoryValue, 3, 1, 1, 1);

        toolButton = new QToolButton(PluginsManagerDialog);
        toolButton->setObjectName(QString::fromUtf8("toolButton"));

        gridLayout->addWidget(toolButton, 3, 2, 1, 1);

        buttonBox = new QDialogButtonBox(PluginsManagerDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 4, 1, 1, 2);


        horizontalLayout->addLayout(gridLayout);

        tabWidget = new QTabWidget(PluginsManagerDialog);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(1);
        sizePolicy3.setVerticalStretch(1);
        sizePolicy3.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy3);
        tabWidget->setAutoFillBackground(false);
        tabWidget->setStyleSheet(QString::fromUtf8(""));
        tab_Overview = new QWidget();
        tab_Overview->setObjectName(QString::fromUtf8("tab_Overview"));
        verticalLayout = new QVBoxLayout(tab_Overview);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        textEdit_Description = new QTextEdit(tab_Overview);
        textEdit_Description->setObjectName(QString::fromUtf8("textEdit_Description"));
        sizePolicy3.setHeightForWidth(textEdit_Description->sizePolicy().hasHeightForWidth());
        textEdit_Description->setSizePolicy(sizePolicy3);
        textEdit_Description->setAutoFillBackground(false);
        textEdit_Description->setStyleSheet(QString::fromUtf8(""));
        textEdit_Description->setReadOnly(true);

        verticalLayout->addWidget(textEdit_Description);

        tabWidget->addTab(tab_Overview, QString());

        horizontalLayout->addWidget(tabWidget);


        retranslateUi(PluginsManagerDialog);
        QObject::connect(buttonBox, SIGNAL(rejected()), PluginsManagerDialog, SLOT(reject()));
        QObject::connect(buttonBox, SIGNAL(accepted()), PluginsManagerDialog, SLOT(accept()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(PluginsManagerDialog);
    } // setupUi

    void retranslateUi(QDialog *PluginsManagerDialog)
    {
        PluginsManagerDialog->setWindowTitle(QApplication::translate("PluginsManagerDialog", "Manage Plugins", 0, QApplication::UnicodeUTF8));
        label_Title->setText(QApplication::translate("PluginsManagerDialog", "To enable / disable or show / hide a plugin, click its checkbox and confirm it with the OK button.", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget_Plugins->headerItem();
        ___qtreewidgetitem->setText(1, QApplication::translate("PluginsManagerDialog", "Plugin", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem->setText(0, QApplication::translate("PluginsManagerDialog", "Enabled", 0, QApplication::UnicodeUTF8));
        label_Filter->setText(QApplication::translate("PluginsManagerDialog", "Filter: ", 0, QApplication::UnicodeUTF8));
        label_PluginDirectory->setText(QApplication::translate("PluginsManagerDialog", "Plugin Directory:", 0, QApplication::UnicodeUTF8));
        toolButton->setText(QApplication::translate("PluginsManagerDialog", "...", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_Overview), QApplication::translate("PluginsManagerDialog", "Overview", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class PluginsManagerDialog: public Ui_PluginsManagerDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLUGINSMANAGERDIALOG_H
