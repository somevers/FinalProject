#ifndef ADD_H
#define ADD_H

#include <QWidget>
#include <QTcpSocket>
#include <QtNetwork>
#include <QCloseEvent>

namespace Ui {
class add;
}

class add : public QWidget
{
    Q_OBJECT

public:
    explicit add(QWidget *parent = nullptr);
    ~add();
    bool eventFilter(QObject *obj, QEvent *event);

private:
    Ui::add *ui;
    QTcpSocket *tcpsocket;
    QString myAccount;

signals:
    void sendAddClose(bool);
public slots:
    void getAddAccount(QString account);

private slots:
    void tcpServerConnect();
    void on_sendButton_clicked();
    void on_user1_clicked();
    void readMessage();

};

#endif // ADD_H
