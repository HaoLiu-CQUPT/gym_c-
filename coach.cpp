#include "coach.h"

Coach::Coach()
    : id(""), name(""), phone(""), gender(""), hireDate(QDate::currentDate()), 
      salary(0.0), specialty(""), status("在职")
{
}

Coach::Coach(const QString& id, const QString& name, const QString& phone, 
             const QString& gender, const QDate& hireDate, double salary)
    : id(id), name(name), phone(phone), gender(gender), hireDate(hireDate), 
      salary(salary), specialty(""), status("在职")
{
}





