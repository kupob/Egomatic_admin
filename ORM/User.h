#ifndef USER_H
#define USER_H

#include <QString>
#include <QList>
#include <QVariant>
#include <QDateTime>
#include <QCryptographicHash>

class User
{
public:
    User()
    {
        isAdmin = false;
        isActive = true;
    }

    bool isValid() { return !userId.isEmpty(); }

    QString     userId;         //  userid uuid NOT NULL, -- Идентификатор клиента
    QString     login;          //  login character varying(32), -- Логин пользователя
    QString     password;       //  password character varying(32), -- Пароль
    QString     name;           //  password character varying(32), -- ФИО пользователя
    bool        isAdmin;        //  isadmin boolean DEFAULT false, -- Флаг прав администратора
    bool        isActive;       //  isactive boolean DEFAULT true, -- Флаг активности

    static const int fieldCount = 6;
    static const int columnCount = 4;

public:
    QVariant data(int position) const
    {
        switch (position) {
        case 0:     return QVariant::fromValue(login);
        case 1:     return QVariant::fromValue(QString("********"));
        case 2:     return QVariant::fromValue(name);
        case 3:
        {
            return isAdmin ? QObject::tr("Да") : QObject::tr("Нет");
        }
        default:    return QVariant();
        }
    }

    void setData(int position, QVariant value)
    {
        switch (position) {
        case 0:
            login = value.toString();
            break;
        case 1:
        {
            QString rawPassword = value.toString();
            password = QCryptographicHash::hash(QString("egomatic").toUtf8() + rawPassword.toUtf8(), QCryptographicHash::Md5).toHex();
            break;
        }
        case 2:
            name = value.toString();
            break;
        case 3:
            isAdmin = value.toBool();
            break;
        default:
            break;
        }
    }

    static QVariant headerData(int position)
    {
        switch (position) {
        case 0:     return QString("Логин пользователя");
        case 1:     return QString("Пароль");
        case 2:     return QString("ФИО пользователя");
        case 3:     return QString("Администратор");
        default:    return QVariant();
        }
    }

    static QList<User> convertFromData(QList< QList<QVariant> > data)
    {
        QList<User> result;

        foreach (auto singleData, data)
        {
            Q_ASSERT(singleData.size() == fieldCount);

            User user;
            user.userId   = singleData.value(0).toString();
            user.login    = singleData.value(1).toString();
            user.password = singleData.value(2).toString();
            user.name     = singleData.value(3).toString();
            user.isAdmin  = singleData.value(4).toBool();
            user.isActive = singleData.value(5).toBool();

            result.append(user);
        }

        return result;
    }
};

#endif // USER_H
