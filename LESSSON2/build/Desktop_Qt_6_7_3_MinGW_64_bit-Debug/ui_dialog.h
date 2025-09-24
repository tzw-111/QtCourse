/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_3;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton_3;
    QSpacerItem *horizontalSpacer;
    QTextEdit *textEdit;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *btnClear;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_2;
    QPushButton *btnexit;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName("Dialog");
        Dialog->resize(884, 607);
        verticalLayout = new QVBoxLayout(Dialog);
        verticalLayout->setObjectName("verticalLayout");
        groupBox_2 = new QGroupBox(Dialog);
        groupBox_2->setObjectName("groupBox_2");
        horizontalLayout = new QHBoxLayout(groupBox_2);
        horizontalLayout->setObjectName("horizontalLayout");
        checkBox = new QCheckBox(groupBox_2);
        checkBox->setObjectName("checkBox");

        horizontalLayout->addWidget(checkBox);

        checkBox_2 = new QCheckBox(groupBox_2);
        checkBox_2->setObjectName("checkBox_2");

        horizontalLayout->addWidget(checkBox_2);

        checkBox_3 = new QCheckBox(groupBox_2);
        checkBox_3->setObjectName("checkBox_3");

        horizontalLayout->addWidget(checkBox_3);


        verticalLayout->addWidget(groupBox_2);

        groupBox = new QGroupBox(Dialog);
        groupBox->setObjectName("groupBox");
        horizontalLayout_2 = new QHBoxLayout(groupBox);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        radioButton = new QRadioButton(groupBox);
        radioButton->setObjectName("radioButton");

        horizontalLayout_2->addWidget(radioButton);

        radioButton_2 = new QRadioButton(groupBox);
        radioButton_2->setObjectName("radioButton_2");

        horizontalLayout_2->addWidget(radioButton_2);

        radioButton_3 = new QRadioButton(groupBox);
        radioButton_3->setObjectName("radioButton_3");

        horizontalLayout_2->addWidget(radioButton_3);


        verticalLayout->addWidget(groupBox);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        verticalLayout->addItem(horizontalSpacer);

        textEdit = new QTextEdit(Dialog);
        textEdit->setObjectName("textEdit");

        verticalLayout->addWidget(textEdit);

        groupBox_3 = new QGroupBox(Dialog);
        groupBox_3->setObjectName("groupBox_3");
        horizontalLayout_3 = new QHBoxLayout(groupBox_3);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        btnClear = new QPushButton(groupBox_3);
        btnClear->setObjectName("btnClear");

        horizontalLayout_3->addWidget(btnClear);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        pushButton_2 = new QPushButton(groupBox_3);
        pushButton_2->setObjectName("pushButton_2");

        horizontalLayout_3->addWidget(pushButton_2);

        btnexit = new QPushButton(groupBox_3);
        btnexit->setObjectName("btnexit");

        horizontalLayout_3->addWidget(btnexit);


        verticalLayout->addWidget(groupBox_3);


        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "Dialog", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("Dialog", "\346\240\274\345\274\217", nullptr));
        checkBox->setText(QCoreApplication::translate("Dialog", "underline", nullptr));
        checkBox_2->setText(QCoreApplication::translate("Dialog", "itatic", nullptr));
        checkBox_3->setText(QCoreApplication::translate("Dialog", "bold", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Dialog", "\351\242\234\350\211\262", nullptr));
        radioButton->setText(QCoreApplication::translate("Dialog", "black", nullptr));
        radioButton_2->setText(QCoreApplication::translate("Dialog", "red", nullptr));
        radioButton_3->setText(QCoreApplication::translate("Dialog", "blue", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("Dialog", "GroupBox", nullptr));
        btnClear->setText(QCoreApplication::translate("Dialog", "\346\270\205\351\231\244", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Dialog", "\347\241\256\350\256\244", nullptr));
        btnexit->setText(QCoreApplication::translate("Dialog", "\351\200\200\345\207\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
