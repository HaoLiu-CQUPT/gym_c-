#ifndef USER_H
#define USER_H

#include <QString>

// 用户角色枚举
enum class UserRole {
    Admin,      // 管理员
    Reception,  // 前台
    Coach       // 教练
};

// 用户类
class User
{
public:
    User();
    User(const QString& username, const QString& password, UserRole role);
    
    QString getUsername() const { return username; }
    QString getPassword() const { return password; }
    UserRole getRole() const { return role; }
    
    void setUsername(const QString& username) { this->username = username; }
    void setPassword(const QString& password) { this->password = password; }
    void setRole(UserRole role) { this->role = role; }
    
    bool checkPassword(const QString& password) const;
    QString getRoleString() const;
    
private:
    QString username;      // 用户名
    QString password;      // 密码
    UserRole role;         // 角色
};

#endif // USER_H

