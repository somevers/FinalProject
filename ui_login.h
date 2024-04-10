/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Login
{
public:
    QFrame *Login_background;
    QLabel *account_label;
    QLabel *password_label;
    QLineEdit *account_Edit;
    QLineEdit *password_Edit;
    QPushButton *register_button;
    QPushButton *lost_password_button;
    QPushButton *login_button;
    QLabel *tip_label;

    void setupUi(QWidget *Login)
    {
        if (Login->objectName().isEmpty())
            Login->setObjectName(QString::fromUtf8("Login"));
        Login->resize(800, 600);
        Login_background = new QFrame(Login);
        Login_background->setObjectName(QString::fromUtf8("Login_background"));
        Login_background->setGeometry(QRect(0, 0, 801, 601));
        Login_background->setStyleSheet(QString::fromUtf8("background-image: url(:/image/Login_background.png);"));
        Login_background->setFrameShape(QFrame::StyledPanel);
        Login_background->setFrameShadow(QFrame::Raised);
        account_label = new QLabel(Login_background);
        account_label->setObjectName(QString::fromUtf8("account_label"));
        account_label->setGeometry(QRect(150, 290, 71, 51));
        account_label->setStyleSheet(QString::fromUtf8("color:rgb(255, 255, 255);\n"
"font: 13pt \"\345\256\213\344\275\223\";"));
        password_label = new QLabel(Login_background);
        password_label->setObjectName(QString::fromUtf8("password_label"));
        password_label->setGeometry(QRect(150, 380, 71, 41));
        password_label->setStyleSheet(QString::fromUtf8("color:rgb(255, 255, 255);\n"
"font: 13pt \"\345\256\213\344\275\223\";"));
        account_Edit = new QLineEdit(Login_background);
        account_Edit->setObjectName(QString::fromUtf8("account_Edit"));
        account_Edit->setGeometry(QRect(240, 300, 291, 41));
        account_Edit->setStyleSheet(QString::fromUtf8("color:rgb(255, 255, 255)"));
        password_Edit = new QLineEdit(Login_background);
        password_Edit->setObjectName(QString::fromUtf8("password_Edit"));
        password_Edit->setGeometry(QRect(240, 380, 291, 41));
        register_button = new QPushButton(Login_background);
        register_button->setObjectName(QString::fromUtf8("register_button"));
        register_button->setGeometry(QRect(560, 300, 131, 41));
        register_button->setStyleSheet(QString::fromUtf8("color:rgb(255, 255, 255);\n"
"font: 12pt \"\345\256\213\344\275\223\";"));
        lost_password_button = new QPushButton(Login_background);
        lost_password_button->setObjectName(QString::fromUtf8("lost_password_button"));
        lost_password_button->setGeometry(QRect(560, 380, 131, 41));
        lost_password_button->setStyleSheet(QString::fromUtf8("color:rgb(255, 255, 255);\n"
"font: 12pt \"\345\256\213\344\275\223\";"));
        login_button = new QPushButton(Login_background);
        login_button->setObjectName(QString::fromUtf8("login_button"));
        login_button->setGeometry(QRect(310, 470, 171, 51));
        login_button->setStyleSheet(QString::fromUtf8("color:rgb(255, 255, 255);\n"
"font: 20pt \"\345\256\213\344\275\223\";"));
        tip_label = new QLabel(Login_background);
        tip_label->setObjectName(QString::fromUtf8("tip_label"));
        tip_label->setGeometry(QRect(600, 550, 171, 31));
        tip_label->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(255, 255, 255);\n"
"font: 12pt \"\345\256\213\344\275\223\";"));

        retranslateUi(Login);

        QMetaObject::connectSlotsByName(Login);
    } // setupUi

    void retranslateUi(QWidget *Login)
    {
        Login->setWindowTitle(QCoreApplication::translate("Login", "Login", nullptr));
        account_label->setText(QCoreApplication::translate("Login", "Account", nullptr));
        password_label->setText(QCoreApplication::translate("Login", "Password", nullptr));
        register_button->setText(QCoreApplication::translate("Login", "Register", nullptr));
        lost_password_button->setText(QCoreApplication::translate("Login", "Forget Password", nullptr));
        login_button->setText(QCoreApplication::translate("Login", "Login", nullptr));
        tip_label->setText(QCoreApplication::translate("Login", "no account", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
