#include "member.h"

Member::Member()
    : id(""), name(""), phone(""), gender(""), joinDate(QDate::currentDate()), 
      balance(0.0), status("正常"), note("")
{
}

Member::Member(const QString& id, const QString& name, const QString& phone, 
               const QString& gender, const QDate& joinDate, double balance)
    : id(id), name(name), phone(phone), gender(gender), joinDate(joinDate), 
      balance(balance), status("正常"), note("")
{
}

bool Member::consume(double amount)
{
    if (balance >= amount) {
        balance -= amount;
        return true;
    }
    return false;
}





