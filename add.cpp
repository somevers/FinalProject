#include "add.h"
#include "ui_add.h"

#include <QResizeEvent>
#include <QCloseEvent>
#include <QtNetwork>
#include <QTcpSocket>
#include <QStringList>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextCursor>

add::add(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::add)
{
    ui->setupUi(this);
    this->installEventFilter(this);
}

add::~add()
{
    delete ui;
}

bool add::eventFilter(QObject *obj, QEvent *event){
    if(obj == this){
        if(event->type() == QCloseEvent::Close){
            qDebug() << "关闭注册页面";
            emit sendAddClose(true);
        }else{
            return false;
        }
    }
    return QWidget::eventFilter(obj, event);
}

void add::getAddAccount(QString account) {
    // 在这里处理收到的账号信息，例如在界面上显示该账号信息
    myAccount = account;
    tcpServerConnect();
    return;
    qDebug() << "账号"<<account;
}

void add::tcpServerConnect(){
    //实例化socket
    tcpsocket = new QTcpSocket(this);
    //断开现有连接
    tcpsocket->abort();
    //连接到本地的7777端口
    tcpsocket->connectToHost(QHostAddress::LocalHost,7777);
    //有可读信息，发送readyRead()
    connect(tcpsocket,SIGNAL(readyRead()),
            this,SLOT(readMessage()));
}

void add::on_sendButton_clicked()
{
    QString string = "search|" +myAccount+ "|"+ui->sendMsgLine->text();

    QByteArray message;
    //以只读打开QByteArray，并设置版本，服务端客户端要一致
    QDataStream out(&message,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_14);
    //写入输出流
    out << string;
    qDebug() << string;
    //发送信息
    tcpsocket->write(message);
    //面板添加信息
    ui->sendMsgLine->clear();
    return;
}

void add::on_user1_clicked()
{
    QString string = "addFriend|" +myAccount+ "|"+ui->user1->text();

    QByteArray message;
    //以只读打开QByteArray，并设置版本，服务端客户端要一致
    QDataStream out(&message,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_14);
    //写入输出流
    out << string;
    qDebug() << string;
    //发送信息
    tcpsocket->write(message);
    //面板添加信息
    return;
}

void add::readMessage()
{
    //实例化套接字的输入流，读信息
    QDataStream in(tcpsocket);
    in.setVersion(QDataStream::Qt_5_14);

    QString greeting;
    //将信息写入greeting读取信息
    in >> greeting;
    //字符串分割
    QStringList msg = greeting.split("|");
    if(msg[0] == "searchResult"){
        if(myAccount == msg[1]){
        QStringList userList;
        userList << ui->user1->text() << ui->user1_2->text() << ui->user1_3->text();
        for(int i=1; i+1<msg.length();i++){
            userList[i-1] = msg[i+1];
        }
        ui->user1->setText(userList.value(0));
        ui->user1_2->setText(userList.value(1));
        ui->user1_3->setText(userList.value(2));
        }
    }
}
