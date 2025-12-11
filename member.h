#ifndef MEMBER_H
#define MEMBER_H

#include <QString>
#include <QDate>

// 会员类
class Member
{
public:
    Member();
    Member(const QString& id, const QString& name, const QString& phone, 
           const QString& gender, const QDate& joinDate, double balance = 0.0);
    
    // Getter方法
    QString getId() const { return id; }
    QString getName() const { return name; }
    QString getPhone() const { return phone; }
    QString getGender() const { return gender; }
    QDate getJoinDate() const { return joinDate; }
    double getBalance() const { return balance; }
    QString getStatus() const { return status; }
    QString getNote() const { return note; }
    
    // Setter方法
    void setId(const QString& id) { this->id = id; }
    void setName(const QString& name) { this->name = name; }
    void setPhone(const QString& phone) { this->phone = phone; }
    void setGender(const QString& gender) { this->gender = gender; }
    void setJoinDate(const QDate& date) { this->joinDate = date; }
    void setBalance(double balance) { this->balance = balance; }
    void setStatus(const QString& status) { this->status = status; }
    void setNote(const QString& note) { this->note = note; }
    
    // 充值
    void recharge(double amount) { balance += amount; }
    
    // 消费
    bool consume(double amount);
    
private:
    QString id;         // 会员ID
    QString name;       // 姓名
    QString phone;      // 电话
    QString gender;     // 性别
    QDate joinDate;     // 入会日期
    double balance;     // 余额
    QString status;     // 状态（正常/暂停/到期）
    QString note;       // 备注
};

#endif // MEMBER_H




