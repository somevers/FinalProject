#include "user.h"
#include "search.h"
#include "ui_user.h"
#include "aesEncryption.h"
#include "passwordHelper.h"

#include <QResizeEvent>
#include <QCloseEvent>
#include <QtNetwork>
#include <QTcpSocket>
#include <QStringList>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextCursor>
#include <QLayout>

#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/bn.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

User::User(QString title) : ui(new Ui::User)
{
    qDebug() << "是否来到";
    ui->setupUi(this);
    QPixmap pix;
    userTitle = title;
    setWindowTitle(title);
    qDebug() << "是否来到";
    pix.load(":image/img/head.png");
    pix = pix.scaled(QSize(80,80));

    ui->headLabel->setPixmap(pix);
    ui->headLabel->resize(QSize(80,80));
    ui->headLabel->setToolTip("头像");

    ui->userNameLabel->setText(userTitle);
    ui->userSignLabel->setText("I'm  so handsome");
    ui->userSignLabel->setToolTip("个性签名！");

    this->installEventFilter(this);
    ui->sendMsgLine->installEventFilter(this);
}

User::~User()
{
    delete ui;
}

void User::on_sendButton_clicked()
{
    if(DH(myAccount,yourAccount)){
        qDebug() << "DH检验成功";
        sendMessage();
    }
}
void User::on_sendButton_2_clicked()
{
    QString inputFilePath = "C:/Users/snever/Desktop/CSChat-master/ChatClient/"+myAccount+"-"+yourAccount+".txt";
        QFile inputFile(inputFilePath);
        if (!inputFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "无法打开文件：" << inputFilePath;
            return;
        }
        int lineCount = 0;
        QTextStream in(&inputFile);
        while (!in.atEnd()) {
            in.readLine();
            lineCount++;
        }
        inputFile.seek(0); // 将文件指针重新定位到文件开头

        // 创建新的txt文件
        QString outputFilePath = "C:/Users/snever/Desktop/CSChat-master/ChatClient/report.txt";
        QFile outputFile(outputFilePath);
        if (!outputFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qDebug() << "无法创建文件：" << outputFilePath;
            return;
        }

        // 在第一行写入文件行数
        QTextStream out(&outputFile);
        out << lineCount << "\n";

        // 逐行复制打开的内容
        while (!in.atEnd()) {
            QString line = in.readLine();
            out << line << "\n";
        }
        inputFile.seek(0);
        QString fileContent = in.readAll();
        QString key("1234567812345678");
        QString iv("1234567812345678");
        QString encrypt = PasswordHelper::aesEncryption(fileContent,key,iv);
        out << encrypt;
        // 关闭文件
        inputFile.close();
        outputFile.close();
}
void User::on_sendButton_3_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(nullptr, "选择文件", "", "Text Files (*.txt)");
    if (filePath.isEmpty()) {
        qDebug() << "用户取消了选择文件操作";
        return;
    }
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "无法打开文件：" << filePath;
        return;
    }
    QTextStream in(&file);
        QString fileContent;
        QString line = in.readLine();
        bool ok;
        int n = line.toInt(&ok);
        if (!ok) {
            qDebug() << "文件格式错误：第一行应该是一个整数";
            return;
        }
        for (int i = 0; i < n && !in.atEnd(); ++i) {
            fileContent += in.readLine() + "\n";
        }
        QString en = in.readLine();
        QString key("1234567812345678");
        QString iv("1234567812345678");
        QString encrypt = PasswordHelper::aesEncryption(fileContent,key,iv);
        if (en==encrypt){
            QMessageBox::information(nullptr, "Result", "Report is legal");
        }else{
            QMessageBox::information(nullptr, "Result", "Report is illegal");
        }
        // 关闭文件
        file.close();
        // 输出读取的文本
        qDebug() << "读取的文本内容：";
        qDebug() << fileContent;
       return;
}
void User::on_sendButton_4_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("选择图像文件"), "", tr("图像文件 (*.png *.jpg *.bmp)"));
    if (filePath.isEmpty()) {
        qDebug() << "用户取消了选择文件操作";
        return;
    }
    QPixmap pixmap(filePath);
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::WriteOnly);
    pixmap.save(&buffer, "PNG");
        // 关闭文件
        // 输出读取的文本
    QString key("1234567812345678");
    QString iv("1234567812345678");
    QString str = QString(byteArray.toBase64());
    qDebug() << "QByteArray: " << byteArray;
    qDebug() << "str: " << str;

    QString encrypt_str =  rsa_pri_encrypt_base64("client");
    QString string = "img|"+yourAccount + "|" + myAccount + "|" +str +"|"+encrypt_str;
    qDebug() << "string: " << string;
    QByteArray message;
    //以只读打开QByteArray，并设置版本，服务端客户端要一致
    QDataStream out(&message,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_14);
    //写入输出流
    out << string;
    tcpsocket->write(message);
    ui->chatEidt->append(tr("%1 :%2").arg("img").arg(myAccount));       //添加消息
    ui->chatEidt->setAlignment(Qt::AlignRight);
    // 获取TextEdit的文档
    QTextDocument *document = ui->chatEidt->document();

    // 创建QTextCursor以插入图片
    QTextCursor cursor = ui->chatEidt->textCursor();

    // 移动到文档末尾
    cursor.movePosition(QTextCursor::End);
    QTextBlockFormat blockFormat = cursor.blockFormat();
    blockFormat.setAlignment(Qt::AlignRight);
    cursor.setBlockFormat(blockFormat);
    cursor.insertImage(pixmap.toImage());
       return;
}
void User::on_sendButton_5_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("选择音频文件"), "", tr("音频文件 (*.mp3 *.wav)"));
    if (filePath.isEmpty()) {
        qDebug() << "用户取消了选择文件操作";
        return;
    }
    QFile audioFile(filePath);
        if (!audioFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "Failed to open file";
            return;
        }
;
    QByteArray audioData = audioFile.readAll();
    audioFile.close();
    QString content = QString(audioData.toBase64());
        // 关闭文件
        // 输出读取的文本
    QString key("1234567812345678");
    QString iv("1234567812345678");
    QString str = content;
    qDebug() << "str: " << str;

    QString encrypt_str =  rsa_pri_encrypt_base64("client");
    QString string = "mp3|"+yourAccount + "|" + myAccount + "|" +str +"|"+encrypt_str;
    qDebug() << "string: " << string;
    QByteArray message;
    //以只读打开QByteArray，并设置版本，服务端客户端要一致
    QDataStream out(&message,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_14);
    //写入输出流
    out << string;
    tcpsocket->write(message);
    ui->chatEidt->append(tr("%1 :%2").arg("mp3").arg(myAccount));       //添加消息
    ui->chatEidt->setAlignment(Qt::AlignRight);
    // 获取TextEdit的文档
    //QPushButton *playButton = new QPushButton("Play Audio", this);

    // 创建一个容器，作为按钮的父部件
    QWidget *containerWidget = new QWidget(ui->chatEidt);
    QVBoxLayout *containerLayout = new QVBoxLayout(containerWidget);

    // 创建一个播放按钮
    QPushButton *playButton = new QPushButton("Play", containerWidget);

    // 将按钮添加到容器的布局管理器中
    containerLayout->addWidget(playButton);

    // 设置容器为 QTextEdit 的视口
    ui->chatEidt->setViewport(containerWidget);
    // 在按钮被点击时立即播放音频
    connect(playButton, &QPushButton::clicked, this, [=]() {
        // 获取音频内容

        // 直接调用播放音频的函数
        playAudio(content);
    });
    return;
    /*QFile audioFile("C:/Users/snever/Desktop/test3.mp3");
    audioFile.open(QIODevice::ReadOnly);
    QByteArray audioData = audioFile.readAll();
    QBuffer *buffer = new QBuffer();
        buffer->setData(audioData);

        // 打开缓冲区
        if (!buffer->open(QIODevice::ReadOnly)) {
            qDebug() << "Failed to open buffer for reading.";
            delete buffer;
            return;
        }

        // 创建 QMediaPlayer 对象
        QMediaPlayer *player = new QMediaPlayer();

        // 设置音频源为缓冲区
        player->setMedia(QMediaContent(), buffer);

        // 播放音频
        player->play();*/
}
void User::on_sendButton_6_clicked()
{
    QString filePath = "C:/Users/snever/Desktop/smile.bmp";
    if (filePath.isEmpty()) {
        qDebug() << "用户取消了选择文件操作";
        return;
    }
    QPixmap pixmap(filePath);
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::WriteOnly);
    pixmap.save(&buffer, "PNG");
        // 关闭文件
        // 输出读取的文本
    QString key("1234567812345678");
    QString iv("1234567812345678");
    QString str = QString(byteArray.toBase64());
    qDebug() << "QByteArray: " << byteArray;
    qDebug() << "str: " << str;

    QString encrypt_str =  rsa_pri_encrypt_base64("client");
    QString string = "img|"+yourAccount + "|" + myAccount + "|" +str +"|"+encrypt_str;
    qDebug() << "string: " << string;
    QByteArray message;
    //以只读打开QByteArray，并设置版本，服务端客户端要一致
    QDataStream out(&message,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_14);
    //写入输出流
    out << string;
    tcpsocket->write(message);
    ui->chatEidt->append("   ");       //添加消息
    ui->chatEidt->setAlignment(Qt::AlignRight);
    ui->chatEidt->append(tr("%1 :%2").arg("img").arg(myAccount));       //添加消息
    ui->chatEidt->setAlignment(Qt::AlignRight);
    ui->chatEidt->append("   ");       //添加消息
    ui->chatEidt->setAlignment(Qt::AlignRight);

    // 获取TextEdit的文档
    QTextDocument *document = ui->chatEidt->document();

    // 创建QTextCursor以插入图片
    QTextCursor cursor = ui->chatEidt->textCursor();

    // 移动到文档末尾
    cursor.movePosition(QTextCursor::End);
    QTextBlockFormat blockFormat = cursor.blockFormat();
    blockFormat.setAlignment(Qt::AlignRight);
    cursor.setBlockFormat(blockFormat);
    cursor.insertImage(pixmap.toImage());
       return;
}
void User::on_sendButton_7_clicked()
{
    if(!newSearch){
        qDebug() << "好友";
        newSearch = new search();
        newSearch->show();
        searchFlag = true;
        connect(this,SIGNAL(sendSearchAccount(QString,QString)),
                       newSearch,SLOT(getSearchAccount(QString,QString)));
        emit sendSearchAccount(myAccount,yourAccount);
        connect(newSearch, SIGNAL(sendSearchClose(bool)), this, SLOT(getSearchClose(bool)));
    }
}

void User::getSearchClose(bool flag){
    if(searchFlag == flag)
    {
        qDebug() << "释放搜索页面";
        newSearch->deleteLater();
        newSearch = NULL;
        searchFlag = false;
        qDebug() << "搜索页面已关闭";
        qDebug() << "界面刷新";
    }else{
        qDebug() << "释放搜索页面失败";
    }
}
bool User::eventFilter(QObject *obj, QEvent *event)
{
    Q_UNUSED(event);
    if(obj == ui->sendMsgLine){
        if(event->type() == QEvent::KeyPress){
            QKeyEvent *press = static_cast<QKeyEvent *>(event);
            if(press->key() == Qt::Key_Return){
               sendMessage();
               return true;
            }
        }else
            return false;
    }if(obj == this){
        if(event->type() == QEvent::Close){
            //发送给父窗口
            emit sendAccount(yourAccount);
            return true;
        }else
            return false;
    }else
        return QWidget::eventFilter(obj,event);
    return QWidget::eventFilter(obj,event);
}

void User::getAccount(QString user1, QString user2)
{
    myAccount = user1;
    yourAccount = user2;
    userTitle = yourAccount;
    qDebug() << "发送方: " << myAccount;
    qDebug() << "接收方: " << yourAccount;
    //连接服务器
    tcpServerConnect();
    if(!DH(myAccount,yourAccount)){
        sendDHMessage();
    }
    QString encrypt_str =  rsa_pri_encrypt_base64("123");
    qDebug()<<"加密数据："<<encrypt_str;
    QString decrypt_str = rsa_pub_decrypt_base64(encrypt_str);
    qDebug()<<"解密数据："<<decrypt_str;
    QString name =myAccount+"-"+yourAccount;
    create(name);
    readHistory(name);
}

void User::tcpServerConnect()
{
    //实例化socket
    tcpsocket = new QTcpSocket(this);
    //断开现有连接
    tcpsocket->abort();
    //连接到本地的6666端口
    tcpsocket->connectToHost(QHostAddress::LocalHost,6666);
    //有可读信息，发送readyRead()
    connect(tcpsocket,SIGNAL(readyRead()),
            this,SLOT(readMessage()));
}

void User::sendMessage(){
    //string = 接收方 + | + 发送方 + 发送信息
    QString key("1234567812345678");
    QString iv("1234567812345678");
    if(DH(myAccount,yourAccount)){
        DHkey=getDH(myAccount,yourAccount);
        qDebug() << "从文件中获取到了";
    }
    else{
        qDebug() << "文件里不存在DH";
    }
    QString encrypt = PasswordHelper::aesEncryption(ui->sendMsgLine->text(),DHkey,iv);
    QString encrypt_str =  rsa_pri_encrypt_base64("client");
    QString string = yourAccount + "|" + myAccount + "|" + encrypt+"|"+encrypt_str;
    QString name=myAccount+"-"+yourAccount;
    QString hMessage=myAccount + "|" +ui->sendMsgLine->text();
    writeHistory(hMessage,name);
    QByteArray message;
    //以只读打开QByteArray，并设置版本，服务端客户端要一致
    QDataStream out(&message,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_14);
    //写入输出流
    out << string;
    qDebug() << "发送方-"+myAccount + ": " << string;
    //发送信息
    tcpsocket->write(message);
    //面板添加信息
    ui->chatEidt->append(tr("%1 :%2").arg(ui->sendMsgLine->text()).arg(myAccount));       //添加消息
    ui->chatEidt->setAlignment(Qt::AlignRight);                                       //此条要在添加消息后面，否则前一条消息跟着改变
    qDebug() << tr("%1 -> %2: %3").arg(myAccount).arg(yourAccount).arg(ui->sendMsgLine->text());
    ui->sendMsgLine->clear();
}

void User::sendDHMessage(){
    //string = 接收方 + | + 发送方 + 发送信息

    QString string = "DHKeyGet|" + myAccount + "|" + yourAccount;

    QByteArray message;
    //以只读打开QByteArray，并设置版本，服务端客户端要一致
    QDataStream out(&message,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_14);
    //写入输出流
    out << string;
    qDebug() << "getDH";
    //发送信息
    tcpsocket->write(message);                                   //此条要在添加消息后面，否则前一条消息跟着改变
}

void User::readMessage(){
    //实例化套接字的输入流，读信息
    QString key("1234567812345678");
    QString iv("1234567812345678");
    QDataStream in(tcpsocket);
    in.setVersion(QDataStream::Qt_5_14);
    QString greeting;
    //将信息写入greeting读取信息
    in >> greeting;
    //字符串分割
    qDebug() << greeting;
    QStringList msg = greeting.split("|");
    qDebug() << "接收方:" << msg[0];//my
    qDebug() << "发送方:" << msg[1];//you
    qDebug() << "msg:" << msg[2];
    if(myAccount == msg[0])
    {
        if(DH(myAccount,msg[1])){
            DHkey=getDH(myAccount,msg[1]);
            qDebug() << "从文件中获取到了";
        }
        else{
            qDebug() << "文件里不存在DH";
        }
        QString decrypt = PasswordHelper::aesDecryption(msg[2],DHkey,iv);
        if(rsa_pub_decrypt_base64(msg[3])=="client"){
            qDebug() << "RSA验证成功";
            ui->chatEidt->append(tr("%1: %2").arg(msg[1]).arg(decrypt));        //面板添加
            ui->chatEidt->setAlignment(Qt::AlignLeft);
        }//此条要在添加消息后面
        QString name=myAccount+"-"+yourAccount;
        QString hMessage=yourAccount + "|" +decrypt;
        writeHistory(hMessage,name);
        qDebug() << tr("%1 -> %2: %3").arg(msg[1]).arg(msg[0]).arg(msg[2]);
    }
    if(msg[0] == "server")
    {
        ui->chatEidt->append(tr("Server: %1").arg(msg[1]));
        ui->chatEidt->setAlignment(Qt::AlignCenter);
        qDebug() << tr("Server: %1").arg(msg[1]);
    }
    if(msg[0]== "DHKey"&&myAccount == msg[1]&&!DH(myAccount,msg[2])){
        quint64 primeNumber = 23;
        quint64 generator = 5;
        quint64 myPrivateKey = getSKey(myAccount).toULongLong();
        quint64 yourPublicKey = msg[3].toLongLong();
        qDebug() << "yourPublicKey" << yourPublicKey;
        // Calculate shared secret for Alice and Bob
        quint64 SharedSecret = static_cast<quint64>(qPow(yourPublicKey, myPrivateKey)) % primeNumber;
        qDebug() << "SharedSecret" << SharedSecret;
        // Convert shared secret to QByteArray
        QByteArray sharedSecretBytes(reinterpret_cast<const char*>(&SharedSecret), sizeof(SharedSecret));
        QByteArray hashedKey = QCryptographicHash::hash(sharedSecretBytes, QCryptographicHash::Sha256);
        QString DHKey = hashedKey.toHex().left(16);
        writeDH(myAccount,msg[2],DHKey);
        qDebug() << "写入文件";
    }
    if(msg[0] == "img"&&msg[1]==myAccount)
    {
        QString decrypt = msg[3];
        if(rsa_pub_decrypt_base64(msg[4])=="client"){
            qDebug() << "RSA验证成功";
            ui->chatEidt->append(tr("%1: %2").arg(msg[2]).arg("img"));        //面板添加
            ui->chatEidt->setAlignment(Qt::AlignLeft);
            QByteArray receivedData = QByteArray::fromBase64(decrypt.toLatin1());
            QPixmap receivedPixmap;
            receivedPixmap.loadFromData(receivedData);
            QTextDocument *document = ui->chatEidt->document();
            QTextCursor cursor = ui->chatEidt->textCursor();
            cursor.movePosition(QTextCursor::End);
            QTextBlockFormat blockFormat = cursor.blockFormat();
            blockFormat.setAlignment(Qt::AlignLeft);
            cursor.setBlockFormat(blockFormat);
            cursor.insertImage(receivedPixmap.toImage());
        }//此条要在添加消息后面
        qDebug() << tr("%1 -> %2: %3").arg(msg[1]).arg(msg[0]).arg(msg[2]);
    }
    if (msg[0] == "mp3"&&msg[1]==myAccount) {
            // 创建按钮
        if(rsa_pub_decrypt_base64(msg[4])=="client"){
            ui->chatEidt->append(tr("%1: %2").arg(msg[2]).arg("mp3"));        //面板添加
            ui->chatEidt->setAlignment(Qt::AlignLeft);
            QWidget *containerWidget = new QWidget(ui->chatEidt);
            QVBoxLayout *containerLayout = new QVBoxLayout(containerWidget);

            // 创建一个播放按钮
            QPushButton *playButton = new QPushButton("Play", containerWidget);

            // 将按钮添加到容器的布局管理器中
            containerLayout->addWidget(playButton);

            // 设置容器为 QTextEdit 的视口
            ui->chatEidt->setViewport(containerWidget);

            // 设置按钮的图标为音频图标（假设你有一个音频图标）

            // 在按钮被点击时立即播放音频
            connect(playButton, &QPushButton::clicked, this, [=]() {
                // 获取音频内容
                QString audioContent = msg[3];

                // 直接调用播放音频的函数
                playAudio(audioContent);
            });
        }
    }
    msg.clear();
}

void User::playAudio(QString audioContent) {

    QFile audioFile("C:/Users/snever/Desktop/test.mp3");
        audioFile.open(QIODevice::ReadOnly);
        QByteArray audioData = audioFile.readAll();
        QBuffer *buffer = new QBuffer();
            buffer->setData(audioData);

            // 打开缓冲区
            if (!buffer->open(QIODevice::ReadOnly)) {
                qDebug() << "Failed to open buffer for reading.";
                delete buffer;
                return;
            }

            // 创建 QMediaPlayer 对象
            QMediaPlayer *player = new QMediaPlayer();

            // 设置音频源为缓冲区
            player->setMedia(QMediaContent(), buffer);

            // 播放音频
            player->play();
            connect(player, &QMediaPlayer::stateChanged, [=](QMediaPlayer::State state) {
                    if (state == QMediaPlayer::StoppedState) {
                        delete buffer;
                        delete player;
                    }
                });
}

bool User::DH(QString myAccount,QString yourAccount){
    QFile file("C:/Users/snever/Desktop/CSChat-master/ChatClient/DH.txt");

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "Failed to open file for reading.";
            return false;
        }
        QTextStream in(&file);
        QString line;
        while (!in.atEnd()) {
            line = in.readLine();
            QStringList parts = line.split('|');
            if (parts.size() == 3 && parts[0] == myAccount && parts[1] == yourAccount) {
                // 匹配到记录
                file.close();
                return true;
            }
        }

        file.close();
        return false;
}

void User::writeDH(QString myAccount, QString yourAccount, QString key) {
    QFile file("C:/Users/snever/Desktop/CSChat-master/ChatClient/DH.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << myAccount << "|" << yourAccount << "|" << key << "\n";
        file.close();
    } else {
        qDebug() << "Failed to open file for writing.";
    }
}
void User::writeHistory(QString message,QString name) {
    QFile file("C:/Users/snever/Desktop/CSChat-master/ChatClient/"+name+".txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << message << "\n";
        file.close();
    } else {
        qDebug() << "Failed to open file for writing.";
    }
}
void User::readHistory(QString name){
    QFile file("C:/Users/snever/Desktop/CSChat-master/ChatClient/"+name+".txt");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "Failed to open file for reading.";
            return;
        }
        QTextStream in(&file);
        QString line;
        while (!in.atEnd()) {
            line = in.readLine();
            QStringList parts = line.split('|');
            if (parts.size() == 2 && parts[0] == myAccount) {
                ui->chatEidt->append(tr("%1 :%2").arg(parts[0]).arg(parts[1]));
                ui->chatEidt->setAlignment(Qt::AlignRight);
            }
            if (parts.size() == 2 && parts[0] == yourAccount) {
                ui->chatEidt->append(tr("%1 :%2").arg(parts[0]).arg(parts[1]));
                ui->chatEidt->setAlignment(Qt::AlignLeft);
            }
        }

        file.close();
        return;
}
void User::create(QString name) {
        QString fileName ="C:/Users/snever/Desktop/CSChat-master/ChatClient/"+ name + ".txt";
        QFile file(fileName);
        if (!file.exists()) {
            // 如果文件不存在，则创建文件
            if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                QTextStream stream(&file);
                file.close();
                qDebug() << "File created: " << fileName;
            } else {
                qDebug() << "Failed to create file: " << fileName;
            }
        } else {
            qDebug() << "File already exists: " << fileName;
        }
}

QString User::getDH(QString myAccount, QString yourAccount) {
    QFile file("C:/Users/snever/Desktop/CSChat-master/ChatClient/DH.txt");

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "Failed to open file for reading.";
            return "1234567812345678";
        }
        QTextStream in(&file);
        QString line;
        while (!in.atEnd()) {
            line = in.readLine();
            QStringList parts = line.split('|');
            if (parts.size() == 3 && parts[0] == myAccount && parts[1] == yourAccount) {
                // 匹配到记录
                file.close();
                qDebug() << "读到DH了";
                return parts[2];
            }
        }
        file.close();
        return "1234567812345678";
}

QString User::getSKey(QString myAccount) {
    QFile file("C:/Users/snever/Desktop/CSChat-master/ChatClient/DHP.txt");

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "Failed to open file for reading.";
            return "1234567812345678";
        }
        QTextStream in(&file);
        QString line;
        while (!in.atEnd()) {
            line = in.readLine();
            QStringList parts = line.split('|');
            if (parts.size() == 2 && parts[0] == myAccount) {
                // 匹配到记录
                file.close();
                qDebug() << "读到DH了";
                return parts[1];
            }
        }
        file.close();
        return "1234567812345678";
}
QString User::rsa_pri_encrypt_base64 (const QString& strClearData)
{
    //私钥  长度为512  （使用自己生成的公秘钥）
    char private_key[] = "-----BEGIN PRIVATE KEY-----\n"\
            "MIIBVgIBADANBgkqhkiG9w0BAQEFAASCAUAwggE8AgEAAkEAtvxGHB5wbcM1DQMC\n"\
            "1gqrHydT/+976CNPlWAWBIsbIGoRRYlJcPs8a/IxsV4ZNgETh0TaWyn1Nomn3s0e\n"\
            "qz000QIDAQABAkEAgSjSh/iIXUGjiZqtfs2q+eN1rDqrWDDMdOCMygoyTI7AHCtl\n"\
            "QcCAAsj2a192FYfX97hvhFoLLvkGBENwkXFh0QIhAN3vy1yKOx0/jJAZMdnGriAL\n"\
            "BmaczuL93H+WseJog5k1AiEA0xIHpz5M9ZbEbEhxv1w1tNYv0C+HmGIrbCfB3efV\n"\
            "fK0CIDr0VQALFDLry6oHl09zUJPged3OL8LqjqUx4aT0AGk1AiEAxNDgMBRJAQy4\n"\
            "VlxrLMxYDCtZZGCdqPuJkA22miyPBvUCIQDB5bS0AElPBPkPnUSWnO6uqxQ2svgE\n"\
            "2h7kJD7gm2bTWg==\n"\
            "-----END PRIVATE KEY-----";

    //将字符串键加载到bio对象
    BIO* pKeyBio = BIO_new_mem_buf(private_key, strlen(private_key));
    if (pKeyBio == NULL){
        return "";
    }
    RSA* pRsa = RSA_new();
    pRsa = PEM_read_bio_RSAPrivateKey(pKeyBio, &pRsa, NULL, NULL);
    if ( pRsa == NULL ){
         BIO_free_all(pKeyBio);
         return "";
    }
    int nLen = RSA_size(pRsa);
    char* pEncryptBuf = new char[nLen];
    memset(pEncryptBuf, 0, nLen);
    QByteArray clearDataArry = strClearData.toUtf8();
    int nClearDataLen = clearDataArry.length();
    uchar* pClearData = (uchar*)clearDataArry.data();
    int nSize = RSA_private_encrypt(nClearDataLen,
                                    pClearData,
                                    (uchar*)pEncryptBuf,
                                    pRsa,
                                    RSA_PKCS1_PADDING);

    QString strEncryptData = "";
    if ( nSize >= 0 ){
         QByteArray arry(pEncryptBuf, nSize);
         strEncryptData = arry.toBase64();
    }
    // 释放内存
    delete pEncryptBuf;
    BIO_free_all(pKeyBio);
    RSA_free(pRsa);
    return strEncryptData;
}
QString User::rsa_pub_decrypt_base64(const QString& strDecryptData)
{

    //公钥解密
    char public_key[] = "-----BEGIN PUBLIC KEY-----\n"\
            "MFwwDQYJKoZIhvcNAQEBBQADSwAwSAJBALb8RhwecG3DNQ0DAtYKqx8nU//ve+gj\n"\
            "T5VgFgSLGyBqEUWJSXD7PGvyMbFeGTYBE4dE2lsp9TaJp97NHqs9NNECAwEAAQ==\n"\
            "-----END PUBLIC KEY-----";

    //将字符串键加载到bio对象
    BIO* pKeyBio = BIO_new_mem_buf(public_key, strlen(public_key));
    if (pKeyBio == NULL){
        return "";
    }

    RSA* pRsa = RSA_new();

    pRsa = PEM_read_bio_RSA_PUBKEY(pKeyBio, &pRsa, NULL, NULL);


    if ( pRsa == NULL ){
        BIO_free_all(pKeyBio);
        return "";
    }
    int nLen = RSA_size(pRsa);
    char* pClearBuf = new char[nLen];
    memset(pClearBuf, 0, nLen);
    //解密
    QByteArray decryptDataArry = strDecryptData.toUtf8();
    decryptDataArry = QByteArray::fromBase64(decryptDataArry);
    int nDecryptDataLen = decryptDataArry.length();
    uchar* pDecryptData = (uchar*)decryptDataArry.data();
    int nSize = RSA_public_decrypt(nDecryptDataLen,
                                   pDecryptData,
                                   (uchar*)pClearBuf,
                                   pRsa,
                                   RSA_PKCS1_PADDING);
    QString strClearData = "";
    if ( nSize >= 0 ){
        strClearData = QByteArray(pClearBuf, nSize);
    }

    // 释放内存
    delete pClearBuf;
    BIO_free_all(pKeyBio);
    RSA_free(pRsa);
    return strClearData;
}


