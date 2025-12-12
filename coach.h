#ifndef COACH_H
#define COACH_H

#include <QString>
#include <QDate>

// 教练类
class Coach
{
public:
    Coach();
    Coach(const QString& id, const QString& name, const QString& phone, 
          const QString& gender, const QDate& hireDate, double salary = 0.0);
    
    // Getter方法
    QString getId() const { return id; }
    QString getName() const { return name; }
    QString getPhone() const { return phone; }
    QString getGender() const { return gender; }
    QDate getHireDate() const { return hireDate; }
    double getSalary() const { return salary; }
    QString getSpecialty() const { return specialty; }
    QString getStatus() const { return status; }
    
    // Setter方法
    void setId(const QString& id) { this->id = id; }
    void setName(const QString& name) { this->name = name; }
    void setPhone(const QString& phone) { this->phone = phone; }
    void setGender(const QString& gender) { this->gender = gender; }
    void setHireDate(const QDate& date) { this->hireDate = date; }
    void setSalary(double salary) { this->salary = salary; }
    void setSpecialty(const QString& specialty) { this->specialty = specialty; }
    void setStatus(const QString& status) { this->status = status; }
    
private:
    QString id;         // 教练ID
    QString name;       // 姓名
    QString phone;      // 电话
    QString gender;     // 性别
    QDate hireDate;     // 入职日期
    double salary;      // 薪资
    QString specialty;  // 专长
    QString status;     // 状态（在职/离职）
};

#endif // COACH_H





