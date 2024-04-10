#ifndef PASSWORDHELPER_H
#define PASSWORDHELPER_H

#include <QObject>
#include "aesEncryption.h"
class PasswordHelper : public QObject
{
    Q_OBJECT
public:
    explicit PasswordHelper(QObject *parent = nullptr);

    static QString aesEncryption(const QString val,const QString key,const QString iv);
    static QString aesDecryption(const QString val,const QString key,const QString iv);

};

#endif // PASSWORDHELPER_H
