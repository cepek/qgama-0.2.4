/********************************************************************************
** Form generated from reading UI file 'aboutgnugamadialog.ui'
**
** Created: Wed Mar 24 17:00:34 2010
**      by: Qt User Interface Compiler version 4.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUTGNUGAMADIALOG_H
#define UI_ABOUTGNUGAMADIALOG_H

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

class Ui_AboutGnuGamaDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label_Logo;
    QLabel *label_Text1;
    QLabel *label_Text2;
    QLabel *label_Text3;
    QLabel *label_Text4;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_OK;

    void setupUi(QDialog *AboutGnuGamaDialog)
    {
        if (AboutGnuGamaDialog->objectName().isEmpty())
            AboutGnuGamaDialog->setObjectName(QString::fromUtf8("AboutGnuGamaDialog"));
        AboutGnuGamaDialog->resize(474, 405);
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(AboutGnuGamaDialog->sizePolicy().hasHeightForWidth());
        AboutGnuGamaDialog->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(AboutGnuGamaDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_Logo = new QLabel(AboutGnuGamaDialog);
        label_Logo->setObjectName(QString::fromUtf8("label_Logo"));
        label_Logo->setPixmap(QPixmap(QString::fromUtf8(":/images/gama-local.png")));
        label_Logo->setMargin(3);

        verticalLayout->addWidget(label_Logo);

        label_Text1 = new QLabel(AboutGnuGamaDialog);
        label_Text1->setObjectName(QString::fromUtf8("label_Text1"));
        label_Text1->setAlignment(Qt::AlignJustify|Qt::AlignVCenter);
        label_Text1->setMargin(3);

        verticalLayout->addWidget(label_Text1);

        label_Text2 = new QLabel(AboutGnuGamaDialog);
        label_Text2->setObjectName(QString::fromUtf8("label_Text2"));
        label_Text2->setTextFormat(Qt::RichText);
        label_Text2->setAlignment(Qt::AlignJustify|Qt::AlignVCenter);
        label_Text2->setWordWrap(true);
        label_Text2->setMargin(3);

        verticalLayout->addWidget(label_Text2);

        label_Text3 = new QLabel(AboutGnuGamaDialog);
        label_Text3->setObjectName(QString::fromUtf8("label_Text3"));
        label_Text3->setTextFormat(Qt::RichText);
        label_Text3->setAlignment(Qt::AlignJustify|Qt::AlignVCenter);
        label_Text3->setWordWrap(true);
        label_Text3->setMargin(3);

        verticalLayout->addWidget(label_Text3);

        label_Text4 = new QLabel(AboutGnuGamaDialog);
        label_Text4->setObjectName(QString::fromUtf8("label_Text4"));
        label_Text4->setTextFormat(Qt::RichText);
        label_Text4->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_Text4->setWordWrap(true);
        label_Text4->setMargin(3);

        verticalLayout->addWidget(label_Text4);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(248, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton_OK = new QPushButton(AboutGnuGamaDialog);
        pushButton_OK->setObjectName(QString::fromUtf8("pushButton_OK"));

        horizontalLayout->addWidget(pushButton_OK);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(AboutGnuGamaDialog);
        QObject::connect(pushButton_OK, SIGNAL(clicked()), AboutGnuGamaDialog, SLOT(close()));

        QMetaObject::connectSlotsByName(AboutGnuGamaDialog);
    } // setupUi

    void retranslateUi(QDialog *AboutGnuGamaDialog)
    {
        AboutGnuGamaDialog->setWindowTitle(QApplication::translate("AboutGnuGamaDialog", "About GNU Gama", 0, QApplication::UnicodeUTF8));
        label_Logo->setText(QString());
        label_Text1->setText(QString());
        label_Text2->setText(QString());
        label_Text3->setText(QString());
        label_Text4->setText(QString());
        pushButton_OK->setText(QApplication::translate("AboutGnuGamaDialog", "&OK", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class AboutGnuGamaDialog: public Ui_AboutGnuGamaDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUTGNUGAMADIALOG_H
