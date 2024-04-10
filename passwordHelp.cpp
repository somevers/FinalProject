#include "passwordHelper.h"

PasswordHelper::PasswordHelper(QObject *parent)
    : QObject{parent}
{

}
QString PasswordHelper::aesEncryption(const QString val,const QString key,const QString iv)
{
    AESEncryption encryption(AESEncryption::AES_128, AESEncryption::ECB, AESEncryption::PKCS7);
    QByteArray enBA = encryption.encode(val.toUtf8(), key.toUtf8(),iv.toUtf8());
    return QString::fromUtf8(enBA.toBase64()); //以便网络传输，或保存在 txt型文件中
}

QString PasswordHelper::aesDecryption(const QString val,const QString key,const QString iv)
{
    AESEncryption encryption(AESEncryption::AES_128, AESEncryption::ECB, AESEncryption::PKCS7);
    QByteArray  enBA = QByteArray::fromBase64(val.toUtf8());
    QByteArray deBA = encryption.decode(enBA, key.toUtf8(),iv.toUtf8());
    return QString::fromUtf8(AESEncryption::RemovePadding(deBA, AESEncryption::PKCS7));
}
