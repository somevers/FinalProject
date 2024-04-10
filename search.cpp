#include "search.h"
#include "ui_search.h"

#include <QResizeEvent>
#include <QCloseEvent>
#include <QtNetwork>
#include <QTcpSocket>
#include <QStringList>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextCursor>

search::search(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::search)
{
    ui->setupUi(this);
    this->installEventFilter(this);
}

search::~search()
{
    delete ui;
}

bool search::eventFilter(QObject *obj, QEvent *event){
    if(obj == this){
        if(event->type() == QCloseEvent::Close){
            qDebug() << "关闭注册页面";
            emit sendSearchClose(true);
        }else{
            return false;
        }
    }
    return QWidget::eventFilter(obj, event);
}

void search::getSearchAccount(QString user1,QString user2) {
    // 在这里处理收到的账号信息，例如在界面上显示该账号信息
    myAccount = user1;
    yourAccount = user2;
    return;
}

void search::on_sendButton_clicked()
{
    QFile file("C:/Users/snever/Desktop/CSChat-master/ChatClient/"+myAccount+"-"+yourAccount+".txt");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "无法打开文件：" << file.errorString();
            return;
        }

        QTextStream in(&file);
        QStringList foundLines;

        while (!in.atEnd()) {
            QString line = in.readLine();
            if (line.contains(ui->sendMsgLine->text())) {
                foundLines << line;
            }
        }
        file.close();
    foundLines << "No more";
    foundLines << "No more";
    foundLines << "No more";
    ui->user1->setText(foundLines.value(0));
    ui->user1_2->setText(foundLines.value(1));
    ui->user1_3->setText(foundLines.value(2));
}
