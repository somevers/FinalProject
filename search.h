#ifndef SEARCH_H
#define SEARCH_H

#include <QWidget>
#include <QTcpSocket>
#include <QtNetwork>
#include <QCloseEvent>

namespace Ui {
class search;
}

class search : public QWidget
{
    Q_OBJECT

public:
    explicit search(QWidget *parent = nullptr);
    ~search();
    bool eventFilter(QObject *obj, QEvent *event);

private:
    Ui::search *ui;
    QTcpSocket *tcpsocket;
    QString myAccount;
    QString yourAccount;
signals:
    void sendSearchClose(bool);
public slots:
    void getSearchAccount(QString user1,QString user2);

private slots:
    void on_sendButton_clicked();
};

#endif // SEARCH_H
