/********************************************************************************
** Form generated from reading UI file 'add.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADD_H
#define UI_ADD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_add
{
public:
    QLineEdit *sendMsgLine;
    QPushButton *sendButton;
    QPushButton *user1;
    QPushButton *user1_2;
    QPushButton *user1_3;

    void setupUi(QWidget *add)
    {
        if (add->objectName().isEmpty())
            add->setObjectName(QString::fromUtf8("add"));
        add->resize(493, 547);
        sendMsgLine = new QLineEdit(add);
        sendMsgLine->setObjectName(QString::fromUtf8("sendMsgLine"));
        sendMsgLine->setGeometry(QRect(10, 40, 391, 31));
        sendButton = new QPushButton(add);
        sendButton->setObjectName(QString::fromUtf8("sendButton"));
        sendButton->setGeometry(QRect(410, 40, 81, 34));
        user1 = new QPushButton(add);
        user1->setObjectName(QString::fromUtf8("user1"));
        user1->setGeometry(QRect(70, 110, 331, 51));
        user1->setStyleSheet(QString::fromUtf8(""));
        user1_2 = new QPushButton(add);
        user1_2->setObjectName(QString::fromUtf8("user1_2"));
        user1_2->setGeometry(QRect(70, 200, 331, 51));
        user1_2->setStyleSheet(QString::fromUtf8(""));
        user1_3 = new QPushButton(add);
        user1_3->setObjectName(QString::fromUtf8("user1_3"));
        user1_3->setGeometry(QRect(70, 290, 331, 51));
        user1_3->setStyleSheet(QString::fromUtf8(""));

        retranslateUi(add);

        QMetaObject::connectSlotsByName(add);
    } // setupUi

    void retranslateUi(QWidget *add)
    {
        add->setWindowTitle(QCoreApplication::translate("add", "Form", nullptr));
        sendButton->setText(QCoreApplication::translate("add", "Search", nullptr));
        user1->setText(QString());
        user1_2->setText(QString());
        user1_3->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class add: public Ui_add {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADD_H
