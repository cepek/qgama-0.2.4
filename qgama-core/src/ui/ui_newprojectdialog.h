/********************************************************************************
** Form generated from reading UI file 'newprojectdialog.ui'
**
** Created: Wed Mar 24 17:00:34 2010
**      by: Qt User Interface Compiler version 4.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWPROJECTDIALOG_H
#define UI_NEWPROJECTDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QSpacerItem>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_NewProjectDialog
{
public:
    QHBoxLayout *horizontalLayout;
    QLabel *label_Logo;
    QFrame *line_Vertical;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_Name_And_Location;
    QGridLayout *gridLayout;
    QLabel *label_Project_Name;
    QLineEdit *lineEdit_Project_Name;
    QLabel *label_Project_Location;
    QLineEdit *lineEdit_Project_Location;
    QToolButton *toolButton_Browse;
    QLabel *label_Project_Folder;
    QLineEdit *lineEdit_Project_Folder;
    QLabel *label_Warning;
    QSpacerItem *verticalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *NewProjectDialog)
    {
        if (NewProjectDialog->objectName().isEmpty())
            NewProjectDialog->setObjectName(QString::fromUtf8("NewProjectDialog"));
        NewProjectDialog->setWindowModality(Qt::ApplicationModal);
        NewProjectDialog->resize(500, 325);
        NewProjectDialog->setModal(true);
        horizontalLayout = new QHBoxLayout(NewProjectDialog);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_Logo = new QLabel(NewProjectDialog);
        label_Logo->setObjectName(QString::fromUtf8("label_Logo"));
        label_Logo->setPixmap(QPixmap(QString::fromUtf8(":/images/gama-local-elipse.png")));

        horizontalLayout->addWidget(label_Logo);

        line_Vertical = new QFrame(NewProjectDialog);
        line_Vertical->setObjectName(QString::fromUtf8("line_Vertical"));
        line_Vertical->setFrameShape(QFrame::VLine);
        line_Vertical->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line_Vertical);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox_Name_And_Location = new QGroupBox(NewProjectDialog);
        groupBox_Name_And_Location->setObjectName(QString::fromUtf8("groupBox_Name_And_Location"));
        gridLayout = new QGridLayout(groupBox_Name_And_Location);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_Project_Name = new QLabel(groupBox_Name_And_Location);
        label_Project_Name->setObjectName(QString::fromUtf8("label_Project_Name"));

        gridLayout->addWidget(label_Project_Name, 0, 0, 1, 1);

        lineEdit_Project_Name = new QLineEdit(groupBox_Name_And_Location);
        lineEdit_Project_Name->setObjectName(QString::fromUtf8("lineEdit_Project_Name"));

        gridLayout->addWidget(lineEdit_Project_Name, 0, 1, 1, 1);

        label_Project_Location = new QLabel(groupBox_Name_And_Location);
        label_Project_Location->setObjectName(QString::fromUtf8("label_Project_Location"));

        gridLayout->addWidget(label_Project_Location, 1, 0, 1, 1);

        lineEdit_Project_Location = new QLineEdit(groupBox_Name_And_Location);
        lineEdit_Project_Location->setObjectName(QString::fromUtf8("lineEdit_Project_Location"));
        lineEdit_Project_Location->setReadOnly(true);

        gridLayout->addWidget(lineEdit_Project_Location, 1, 1, 1, 1);

        toolButton_Browse = new QToolButton(groupBox_Name_And_Location);
        toolButton_Browse->setObjectName(QString::fromUtf8("toolButton_Browse"));

        gridLayout->addWidget(toolButton_Browse, 1, 2, 1, 1);

        label_Project_Folder = new QLabel(groupBox_Name_And_Location);
        label_Project_Folder->setObjectName(QString::fromUtf8("label_Project_Folder"));

        gridLayout->addWidget(label_Project_Folder, 2, 0, 1, 1);

        lineEdit_Project_Folder = new QLineEdit(groupBox_Name_And_Location);
        lineEdit_Project_Folder->setObjectName(QString::fromUtf8("lineEdit_Project_Folder"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lineEdit_Project_Folder->sizePolicy().hasHeightForWidth());
        lineEdit_Project_Folder->setSizePolicy(sizePolicy);
        lineEdit_Project_Folder->setReadOnly(true);

        gridLayout->addWidget(lineEdit_Project_Folder, 2, 1, 1, 1);


        verticalLayout->addWidget(groupBox_Name_And_Location);

        label_Warning = new QLabel(NewProjectDialog);
        label_Warning->setObjectName(QString::fromUtf8("label_Warning"));

        verticalLayout->addWidget(label_Warning);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        buttonBox = new QDialogButtonBox(NewProjectDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Help|QDialogButtonBox::Ok);
        buttonBox->setCenterButtons(false);

        verticalLayout->addWidget(buttonBox);


        horizontalLayout->addLayout(verticalLayout);

#ifndef QT_NO_SHORTCUT
        label_Project_Name->setBuddy(lineEdit_Project_Name);
        label_Project_Location->setBuddy(lineEdit_Project_Location);
        label_Project_Folder->setBuddy(lineEdit_Project_Folder);
#endif // QT_NO_SHORTCUT

        retranslateUi(NewProjectDialog);

        QMetaObject::connectSlotsByName(NewProjectDialog);
    } // setupUi

    void retranslateUi(QDialog *NewProjectDialog)
    {
        NewProjectDialog->setWindowTitle(QApplication::translate("NewProjectDialog", "New QGama Project", 0, QApplication::UnicodeUTF8));
        label_Logo->setText(QString());
        groupBox_Name_And_Location->setTitle(QApplication::translate("NewProjectDialog", "Name and Location:", 0, QApplication::UnicodeUTF8));
        label_Project_Name->setText(QApplication::translate("NewProjectDialog", "Project &Name:", 0, QApplication::UnicodeUTF8));
        label_Project_Location->setText(QApplication::translate("NewProjectDialog", "Project &Location:", 0, QApplication::UnicodeUTF8));
        toolButton_Browse->setText(QApplication::translate("NewProjectDialog", "Browse...", 0, QApplication::UnicodeUTF8));
        label_Project_Folder->setText(QApplication::translate("NewProjectDialog", "Project &Folder:", 0, QApplication::UnicodeUTF8));
        lineEdit_Project_Folder->setText(QString());
        label_Warning->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class NewProjectDialog: public Ui_NewProjectDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWPROJECTDIALOG_H
