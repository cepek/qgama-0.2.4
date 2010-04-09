/********************************************************************************
** Form generated from reading UI file 'preferencesdialog.ui'
**
** Created: Wed Mar 24 17:00:33 2010
**      by: Qt User Interface Compiler version 4.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PREFERENCESDIALOG_H
#define UI_PREFERENCESDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStackedWidget>
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PreferencesDialog
{
public:
    QAction *actionAppearence;
    QHBoxLayout *horizontalLayout;
    QListWidget *listWidget;
    QStackedWidget *stackedWidget;
    QWidget *appearance;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidgetAppearence;
    QWidget *general;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label_Font;
    QPushButton *pushButton_Select_Font;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *PreferencesDialog)
    {
        if (PreferencesDialog->objectName().isEmpty())
            PreferencesDialog->setObjectName(QString::fromUtf8("PreferencesDialog"));
        PreferencesDialog->setWindowModality(Qt::ApplicationModal);
        PreferencesDialog->resize(337, 210);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(PreferencesDialog->sizePolicy().hasHeightForWidth());
        PreferencesDialog->setSizePolicy(sizePolicy);
        PreferencesDialog->setModal(true);
        actionAppearence = new QAction(PreferencesDialog);
        actionAppearence->setObjectName(QString::fromUtf8("actionAppearence"));
        horizontalLayout = new QHBoxLayout(PreferencesDialog);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        listWidget = new QListWidget(PreferencesDialog);
        new QListWidgetItem(listWidget);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        sizePolicy.setHeightForWidth(listWidget->sizePolicy().hasHeightForWidth());
        listWidget->setSizePolicy(sizePolicy);
        listWidget->setMinimumSize(QSize(0, 0));
        listWidget->setMaximumSize(QSize(150, 16777215));
        listWidget->setBaseSize(QSize(0, 0));
        listWidget->setResizeMode(QListView::Adjust);

        horizontalLayout->addWidget(listWidget);

        stackedWidget = new QStackedWidget(PreferencesDialog);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(stackedWidget->sizePolicy().hasHeightForWidth());
        stackedWidget->setSizePolicy(sizePolicy1);
        appearance = new QWidget();
        appearance->setObjectName(QString::fromUtf8("appearance"));
        sizePolicy.setHeightForWidth(appearance->sizePolicy().hasHeightForWidth());
        appearance->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(appearance);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tabWidgetAppearence = new QTabWidget(appearance);
        tabWidgetAppearence->setObjectName(QString::fromUtf8("tabWidgetAppearence"));
        sizePolicy.setHeightForWidth(tabWidgetAppearence->sizePolicy().hasHeightForWidth());
        tabWidgetAppearence->setSizePolicy(sizePolicy);
        general = new QWidget();
        general->setObjectName(QString::fromUtf8("general"));
        verticalLayout_2 = new QVBoxLayout(general);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        groupBox = new QGroupBox(general);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_Font = new QLabel(groupBox);
        label_Font->setObjectName(QString::fromUtf8("label_Font"));

        gridLayout->addWidget(label_Font, 0, 0, 1, 1);

        pushButton_Select_Font = new QPushButton(groupBox);
        pushButton_Select_Font->setObjectName(QString::fromUtf8("pushButton_Select_Font"));

        gridLayout->addWidget(pushButton_Select_Font, 0, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 1, 0, 1, 1);


        verticalLayout_2->addWidget(groupBox);

        tabWidgetAppearence->addTab(general, QString());

        verticalLayout->addWidget(tabWidgetAppearence);

        stackedWidget->addWidget(appearance);

        horizontalLayout->addWidget(stackedWidget);


        retranslateUi(PreferencesDialog);
        QObject::connect(listWidget, SIGNAL(currentRowChanged(int)), stackedWidget, SLOT(setCurrentIndex(int)));

        stackedWidget->setCurrentIndex(0);
        tabWidgetAppearence->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(PreferencesDialog);
    } // setupUi

    void retranslateUi(QDialog *PreferencesDialog)
    {
        PreferencesDialog->setWindowTitle(QApplication::translate("PreferencesDialog", "Preferences", 0, QApplication::UnicodeUTF8));
        actionAppearence->setText(QApplication::translate("PreferencesDialog", "Appearence", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = listWidget->isSortingEnabled();
        listWidget->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listWidget->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("PreferencesDialog", "Appearance", 0, QApplication::UnicodeUTF8));
        listWidget->setSortingEnabled(__sortingEnabled);

        groupBox->setTitle(QApplication::translate("PreferencesDialog", "Fonts && Colors:", 0, QApplication::UnicodeUTF8));
        label_Font->setText(QApplication::translate("PreferencesDialog", "Font:", 0, QApplication::UnicodeUTF8));
        pushButton_Select_Font->setText(QString());
        tabWidgetAppearence->setTabText(tabWidgetAppearence->indexOf(general), QApplication::translate("PreferencesDialog", "General", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class PreferencesDialog: public Ui_PreferencesDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PREFERENCESDIALOG_H
