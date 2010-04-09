/********************************************************************************
** Form generated from reading UI file 'aboutqgamadialog.ui'
**
** Created: Wed Mar 24 17:00:34 2010
**      by: Qt User Interface Compiler version 4.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUTQGAMADIALOG_H
#define UI_ABOUTQGAMADIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_AboutQGamaDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label_Logo;
    QLabel *label_Program;
    QLabel *label_Author;
    QLabel *label_License;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_OK;

    void setupUi(QDialog *AboutQGamaDialog)
    {
        if (AboutQGamaDialog->objectName().isEmpty())
            AboutQGamaDialog->setObjectName(QString::fromUtf8("AboutQGamaDialog"));
        AboutQGamaDialog->setWindowModality(Qt::WindowModal);
        AboutQGamaDialog->resize(359, 304);
        AboutQGamaDialog->setModal(true);
        verticalLayout = new QVBoxLayout(AboutQGamaDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_Logo = new QLabel(AboutQGamaDialog);
        label_Logo->setObjectName(QString::fromUtf8("label_Logo"));
        label_Logo->setPixmap(QPixmap(QString::fromUtf8(":/images/rocinante.png")));
        label_Logo->setAlignment(Qt::AlignCenter);
        label_Logo->setMargin(3);

        verticalLayout->addWidget(label_Logo);

        label_Program = new QLabel(AboutQGamaDialog);
        label_Program->setObjectName(QString::fromUtf8("label_Program"));
        label_Program->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_Program->setMargin(3);

        verticalLayout->addWidget(label_Program);

        label_Author = new QLabel(AboutQGamaDialog);
        label_Author->setObjectName(QString::fromUtf8("label_Author"));
        label_Author->setTextFormat(Qt::RichText);
        label_Author->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_Author->setMargin(3);

        verticalLayout->addWidget(label_Author);

        label_License = new QLabel(AboutQGamaDialog);
        label_License->setObjectName(QString::fromUtf8("label_License"));
        label_License->setAlignment(Qt::AlignJustify|Qt::AlignVCenter);
        label_License->setWordWrap(true);
        label_License->setMargin(3);

        verticalLayout->addWidget(label_License);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(248, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton_OK = new QPushButton(AboutQGamaDialog);
        pushButton_OK->setObjectName(QString::fromUtf8("pushButton_OK"));

        horizontalLayout->addWidget(pushButton_OK);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(AboutQGamaDialog);
        QObject::connect(pushButton_OK, SIGNAL(clicked()), AboutQGamaDialog, SLOT(close()));

        QMetaObject::connectSlotsByName(AboutQGamaDialog);
    } // setupUi

    void retranslateUi(QDialog *AboutQGamaDialog)
    {
        AboutQGamaDialog->setWindowTitle(QApplication::translate("AboutQGamaDialog", "About QGama", 0, QApplication::UnicodeUTF8));
        label_Logo->setText(QString());
        label_Program->setText(QString());
        label_Author->setText(QString());
        label_License->setText(QApplication::translate("AboutQGamaDialog", "This program is licensed to you under the terms of the GNU General Public License Version 2 as published by the Free Software Foundation.", 0, QApplication::UnicodeUTF8));
        pushButton_OK->setText(QApplication::translate("AboutQGamaDialog", "&OK", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class AboutQGamaDialog: public Ui_AboutQGamaDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUTQGAMADIALOG_H
