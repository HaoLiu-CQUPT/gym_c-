#include "course.h"

Course::Course()
    : id(""), name(""), coachId(""), coachName(""), 
      startTime(QTime(9, 0)), endTime(QTime(10, 0)),
      duration(60), price(0.0), maxStudents(20), 
      currentStudents(0), dayOfWeek(""), status("进行中")
{
}

Course::Course(const QString& id, const QString& name, const QString& coachId,
               const QString& coachName, const QTime& startTime, const QTime& endTime,
               int duration, double price, int maxStudents)
    : id(id), name(name), coachId(coachId), coachName(coachName),
      startTime(startTime), endTime(endTime), duration(duration),
      price(price), maxStudents(maxStudents), currentStudents(0),
      dayOfWeek(""), status("进行中")
{
}

bool Course::addStudent()
{
    if (currentStudents < maxStudents) {
        currentStudents++;
        return true;
    }
    return false;
}

void Course::removeStudent()
{
    if (currentStudents > 0) {
        currentStudents--;
    }
}
