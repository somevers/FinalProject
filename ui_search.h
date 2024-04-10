/********************************************************************************
** Form generated from reading UI file 'search.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEARCH_H
#define UI_SEARCH_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_search
{
public:
    QLineEdit *sendMsgLine;
    QPushButton *sendButton;
    QPushButton *user1;
    QPushButton *user1_2;
    QPushButton *user1_3;
    QPushButton *user1_4;
    QPushButton *user1_5;
    QPushButton *user1_6;

    void setupUi(QWidget *search)
    {
        if (search->objectName().isEmpty())
            search->setObjectName(QString::fromUtf8("search"));
        search->resize(454, 428);
        sendMsgLine = new QLineEdit(search);
        sendMsgLine->setObjectName(QString::fromUtf8("sendMsgLine"));
        sendMsgLine->setGeometry(QRect(10, 20, 321, 31));
        sendButton = new QPushButton(search);
        sendButton->setObjectName(QString::fromUtf8("sendButton"));
        sendButton->setGeometry(QRect(360, 20, 81, 34));
        user1 = new QPushButton(search);
        user1->setObjectName(QString::fromUtf8("user1"));
        user1->setGeometry(QRect(60, 80, 331, 51));
        user1->setStyleSheet(QString::fromUtf8(""));
        user1_2 = new QPushButton(search);
        user1_2->setObjectName(QString::fromUtf8("user1_2"));
        user1_2->setGeometry(QRect(60, 130, 331, 51));
        user1_2->setStyleSheet(QString::fromUtf8(""));
        user1_3 = new QPushButton(search);
        user1_3->setObjectName(QString::fromUtf8("user1_3"));
        user1_3->setGeometry(QRect(60, 180, 331, 51));
        user1_3->setStyleSheet(QString::fromUtf8(""));
        user1_4 = new QPushButton(search);
        user1_4->setObjectName(QString::fromUtf8("user1_4"));
        user1_4->setGeometry(QRect(60, 230, 331, 51));
        user1_4->setStyleSheet(QString::fromUtf8(""));
        user1_5 = new QPushButton(search);
        user1_5->setObjectName(QString::fromUtf8("user1_5"));
        user1_5->setGeometry(QRect(60, 280, 331, 51));
        user1_5->setStyleSheet(QString::fromUtf8(""));
        user1_6 = new QPushButton(search);
        user1_6->setObjectName(QString::fromUtf8("user1_6"));
        user1_6->setGeometry(QRect(60, 330, 331, 51));
        user1_6->setStyleSheet(QString::fromUtf8(""));

        retranslateUi(search);

        QMetaObject::connectSlotsByName(search);
    } // setupUi

    void retranslateUi(QWidget *search)
    {
        search->setWindowTitle(QCoreApplication::translate("search", "Form", nullptr));
        sendButton->setText(QCoreApplication::translate("search", "Search", nullptr));
        user1->setText(QString());
        user1_2->setText(QString());
        user1_3->setText(QString());
        user1_4->setText(QString());
        user1_5->setText(QString());
        user1_6->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class search: public Ui_search {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEARCH_H
