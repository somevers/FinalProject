#ifndef USER_H
#define USER_H

#include "search.h"
#include <QWidget>
#include <QTcpServer>
#include <QMediaPlayer>

namespace Ui {
class User;
}

class User : public QWidget
{
    Q_OBJECT
public:
    explicit User(QString title);
    ~User();
    QString userTitle;
    bool eventFilter(QObject *obj, QEvent *event);
    bool DH(QString myAccount,QString yourAccount);
private:
    Ui::User *ui;
    QMediaPlayer *player;
    QString myAccount;
    QString yourAccount;
    QString DHkey;
    QTcpSocket *tcpsocket;
    search *newSearch = NULL;
    bool searchFlag = false;
signals:
    void sendAccount(QString);//发送给select界面聊天人账号
    void sendSearchAccount(QString,QString);
public slots:
    void getAccount(QString user1,QString user2);
    void sendMessage();             //向服务器发送信息
    void sendDHMessage();
    void readMessage();             //读取服务器信息
    void tcpServerConnect();        //连接服务器
    void on_sendButton_clicked();
    void on_sendButton_2_clicked();
    void on_sendButton_3_clicked();
    void on_sendButton_4_clicked();
    void on_sendButton_5_clicked();
    void on_sendButton_6_clicked();
    void on_sendButton_7_clicked();
    void playAudio(QString audioContent);
    void writeDH(QString user1,QString user2,QString key);
    void create(QString name);
    void writeHistory(QString message,QString name);
    void readHistory(QString name);
    QString getDH(QString user1,QString user2);
    QString getSKey(QString user1);
    QString rsa_pri_encrypt_base64(const QString &strClearData);
    QString rsa_pub_decrypt_base64(const QString &strDecryptData);
    void getSearchClose(bool flag);
};

#endif // USER_H
