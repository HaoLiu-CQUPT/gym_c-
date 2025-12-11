#include "user.h"

User::User()
    : username(""), password(""), role(UserRole::Reception)
{
}

User::User(const QString& username, const QString& password, UserRole role)
    : username(username), password(password), role(role)
{
}

bool User::checkPassword(const QString& password) const
{
    return this->password == password;
}

QString User::getRoleString() const
{
    switch(role) {
        case UserRole::Admin:
            return "管理员";
        case UserRole::Reception:
            return "前台";
        case UserRole::Coach:
            return "教练";
        default:
            return "未知";
    }
}

