#include "reservation.h"

Reservation::Reservation()
    : id(""), memberId(""), memberName(""), type(ReservationType::Course),
      resourceId(""), resourceName(""), date(QDate::currentDate()),
      startTime(QTime(9, 0)), endTime(QTime(10, 0)), status("已预约"), fee(0.0)
{
}

Reservation::Reservation(const QString& id, const QString& memberId, const QString& memberName,
                         ReservationType type, const QString& resourceId, const QString& resourceName,
                         const QDate& date, const QTime& startTime, const QTime& endTime)
    : id(id), memberId(memberId), memberName(memberName), type(type),
      resourceId(resourceId), resourceName(resourceName), date(date),
      startTime(startTime), endTime(endTime), status("已预约"), fee(0.0)
{
}

QString Reservation::getTypeString() const
{
    switch(type) {
        case ReservationType::Course:
            return "课程预约";
        case ReservationType::Equipment:
            return "器械预约";
        default:
            return "未知";
    }
}





