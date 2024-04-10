/********************************************************************************
** Form generated from reading UI file 'user.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USER_H
#define UI_USER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_User
{
public:
    QLabel *headLabel;
    QLabel *userNameLabel;
    QLabel *userSignLabel;
    QTextEdit *chatEidt;
    QPushButton *sendButton;
    QLineEdit *sendMsgLine;
    QPushButton *sendButton_2;
    QPushButton *sendButton_3;
    QPushButton *sendButton_4;
    QPushButton *sendButton_5;
    QPushButton *sendButton_6;
    QPushButton *sendButton_7;

    void setupUi(QWidget *User)
    {
        if (User->objectName().isEmpty())
            User->setObjectName(QString::fromUtf8("User"));
        User->resize(556, 495);
        headLabel = new QLabel(User);
        headLabel->setObjectName(QString::fromUtf8("headLabel"));
        headLabel->setGeometry(QRect(40, 30, 91, 81));
        headLabel->setStyleSheet(QString::fromUtf8(""));
        userNameLabel = new QLabel(User);
        userNameLabel->setObjectName(QString::fromUtf8("userNameLabel"));
        userNameLabel->setGeometry(QRect(150, 80, 81, 31));
        userNameLabel->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        userSignLabel = new QLabel(User);
        userSignLabel->setObjectName(QString::fromUtf8("userSignLabel"));
        userSignLabel->setGeometry(QRect(30, 100, 171, 21));
        userSignLabel->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        chatEidt = new QTextEdit(User);
        chatEidt->setObjectName(QString::fromUtf8("chatEidt"));
        chatEidt->setGeometry(QRect(30, 130, 491, 251));
        chatEidt->setReadOnly(true);
        sendButton = new QPushButton(User);
        sendButton->setObjectName(QString::fromUtf8("sendButton"));
        sendButton->setGeometry(QRect(440, 430, 81, 34));
        sendMsgLine = new QLineEdit(User);
        sendMsgLine->setObjectName(QString::fromUtf8("sendMsgLine"));
        sendMsgLine->setGeometry(QRect(30, 430, 391, 31));
        sendButton_2 = new QPushButton(User);
        sendButton_2->setObjectName(QString::fromUtf8("sendButton_2"));
        sendButton_2->setGeometry(QRect(350, 80, 81, 34));
        sendButton_3 = new QPushButton(User);
        sendButton_3->setObjectName(QString::fromUtf8("sendButton_3"));
        sendButton_3->setGeometry(QRect(260, 80, 81, 34));
        sendButton_4 = new QPushButton(User);
        sendButton_4->setObjectName(QString::fromUtf8("sendButton_4"));
        sendButton_4->setGeometry(QRect(30, 390, 81, 34));
        sendButton_5 = new QPushButton(User);
        sendButton_5->setObjectName(QString::fromUtf8("sendButton_5"));
        sendButton_5->setGeometry(QRect(120, 390, 81, 34));
        sendButton_6 = new QPushButton(User);
        sendButton_6->setObjectName(QString::fromUtf8("sendButton_6"));
        sendButton_6->setGeometry(QRect(210, 390, 81, 34));
        sendButton_7 = new QPushButton(User);
        sendButton_7->setObjectName(QString::fromUtf8("sendButton_7"));
        sendButton_7->setGeometry(QRect(440, 80, 81, 34));

        retranslateUi(User);

        QMetaObject::connectSlotsByName(User);
    } // setupUi

    void retranslateUi(QWidget *User)
    {
        User->setWindowTitle(QCoreApplication::translate("User", "Form", nullptr));
        headLabel->setText(QString());
        userNameLabel->setText(QString());
        userSignLabel->setText(QString());
        sendButton->setText(QCoreApplication::translate("User", "Send", nullptr));
        sendButton_2->setText(QCoreApplication::translate("User", "save history", nullptr));
        sendButton_3->setText(QCoreApplication::translate("User", "check report", nullptr));
        sendButton_4->setText(QCoreApplication::translate("User", "img", nullptr));
        sendButton_5->setText(QCoreApplication::translate("User", "mp3", nullptr));
        sendButton_6->setText(QCoreApplication::translate("User", "smile", nullptr));
        sendButton_7->setText(QCoreApplication::translate("User", "search", nullptr));
    } // retranslateUi

};

namespace Ui {
    class User: public Ui_User {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USER_H
