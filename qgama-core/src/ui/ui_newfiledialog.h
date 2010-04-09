/********************************************************************************
** Form generated from reading UI file 'newfiledialog.ui'
**
** Created: Wed Mar 24 23:50:13 2010
**      by: Qt User Interface Compiler version 4.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWFILEDIALOG_H
#define UI_NEWFILEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QSpacerItem>
#include <QtGui/QTextBrowser>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_NewFileDialog
{
public:
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label_Logo;
    QSpacerItem *verticalSpacer;
    QFrame *line;
    QGroupBox *groupBox_Choose_File_Type;
    QGridLayout *gridLayout;
    QLabel *label_Project;
    QComboBox *comboBox_Project;
    QLabel *label_Categories;
    QLabel *label_File_Types;
    QLabel *label_Description;
    QTextBrowser *textBrowser_Description;
    QListWidget *listWidget_Categories;
    QListWidget *listWidget_File_Types;

    void setupUi(QDialog *NewFileDialog)
    {
        if (NewFileDialog->objectName().isEmpty())
            NewFileDialog->setObjectName(QString::fromUtf8("NewFileDialog"));
        NewFileDialog->setWindowModality(Qt::ApplicationModal);
        NewFileDialog->resize(755, 351);
        NewFileDialog->setModal(true);
        horizontalLayout = new QHBoxLayout(NewFileDialog);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_Logo = new QLabel(NewFileDialog);
        label_Logo->setObjectName(QString::fromUtf8("label_Logo"));
        label_Logo->setPixmap(QPixmap(QString::fromUtf8(":/images/gama-local-elipse.png")));

        verticalLayout->addWidget(label_Logo);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addLayout(verticalLayout);

        line = new QFrame(NewFileDialog);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line);

        groupBox_Choose_File_Type = new QGroupBox(NewFileDialog);
        groupBox_Choose_File_Type->setObjectName(QString::fromUtf8("groupBox_Choose_File_Type"));
        gridLayout = new QGridLayout(groupBox_Choose_File_Type);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_Project = new QLabel(groupBox_Choose_File_Type);
        label_Project->setObjectName(QString::fromUtf8("label_Project"));

        gridLayout->addWidget(label_Project, 0, 0, 1, 1);

        comboBox_Project = new QComboBox(groupBox_Choose_File_Type);
        comboBox_Project->setObjectName(QString::fromUtf8("comboBox_Project"));

        gridLayout->addWidget(comboBox_Project, 0, 1, 1, 2);

        label_Categories = new QLabel(groupBox_Choose_File_Type);
        label_Categories->setObjectName(QString::fromUtf8("label_Categories"));

        gridLayout->addWidget(label_Categories, 1, 0, 1, 2);

        label_File_Types = new QLabel(groupBox_Choose_File_Type);
        label_File_Types->setObjectName(QString::fromUtf8("label_File_Types"));

        gridLayout->addWidget(label_File_Types, 1, 2, 1, 1);

        label_Description = new QLabel(groupBox_Choose_File_Type);
        label_Description->setObjectName(QString::fromUtf8("label_Description"));

        gridLayout->addWidget(label_Description, 3, 0, 1, 2);

        textBrowser_Description = new QTextBrowser(groupBox_Choose_File_Type);
        textBrowser_Description->setObjectName(QString::fromUtf8("textBrowser_Description"));

        gridLayout->addWidget(textBrowser_Description, 4, 0, 1, 3);

        listWidget_Categories = new QListWidget(groupBox_Choose_File_Type);
        new QListWidgetItem(listWidget_Categories);
        new QListWidgetItem(listWidget_Categories);
        new QListWidgetItem(listWidget_Categories);
        listWidget_Categories->setObjectName(QString::fromUtf8("listWidget_Categories"));

        gridLayout->addWidget(listWidget_Categories, 2, 0, 1, 2);

        listWidget_File_Types = new QListWidget(groupBox_Choose_File_Type);
        listWidget_File_Types->setObjectName(QString::fromUtf8("listWidget_File_Types"));

        gridLayout->addWidget(listWidget_File_Types, 2, 2, 1, 1);


        horizontalLayout->addWidget(groupBox_Choose_File_Type);

#ifndef QT_NO_SHORTCUT
        label_Project->setBuddy(comboBox_Project);
#endif // QT_NO_SHORTCUT

        retranslateUi(NewFileDialog);

        QMetaObject::connectSlotsByName(NewFileDialog);
    } // setupUi

    void retranslateUi(QDialog *NewFileDialog)
    {
        NewFileDialog->setWindowTitle(QApplication::translate("NewFileDialog", "New File", 0, QApplication::UnicodeUTF8));
        label_Logo->setText(QString());
        groupBox_Choose_File_Type->setTitle(QApplication::translate("NewFileDialog", "Choose File Type:", 0, QApplication::UnicodeUTF8));
        label_Project->setText(QApplication::translate("NewFileDialog", "&Project:", 0, QApplication::UnicodeUTF8));
        label_Categories->setText(QApplication::translate("NewFileDialog", "Categories:", 0, QApplication::UnicodeUTF8));
        label_File_Types->setText(QApplication::translate("NewFileDialog", "File Types:", 0, QApplication::UnicodeUTF8));
        label_Description->setText(QApplication::translate("NewFileDialog", "Description:", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = listWidget_Categories->isSortingEnabled();
        listWidget_Categories->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listWidget_Categories->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("NewFileDialog", "Network", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem1 = listWidget_Categories->item(1);
        ___qlistwidgetitem1->setText(QApplication::translate("NewFileDialog", "Settings", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem2 = listWidget_Categories->item(2);
        ___qlistwidgetitem2->setText(QApplication::translate("NewFileDialog", "Protocol", 0, QApplication::UnicodeUTF8));
        listWidget_Categories->setSortingEnabled(__sortingEnabled);

    } // retranslateUi

};

namespace Ui {
    class NewFileDialog: public Ui_NewFileDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWFILEDIALOG_H
