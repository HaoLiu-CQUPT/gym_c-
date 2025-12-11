#ifndef RESERVATION_H
#define RESERVATION_H

#include <QString>
#include <QDate>
#include <QTime>

// 预约类型枚举
enum class ReservationType {
    Course,     // 课程预约
    Equipment   // 器械预约
};

// 预约类
class Reservation
{
public:
    Reservation();
    Reservation(const QString& id, const QString& memberId, const QString& memberName,
                ReservationType type, const QString& resourceId, const QString& resourceName,
                const QDate& date, const QTime& startTime, const QTime& endTime);
    
    // Getter方法
    QString getId() const { return id; }
    QString getMemberId() const { return memberId; }
    QString getMemberName() const { return memberName; }
    ReservationType getType() const { return type; }
    QString getResourceId() const { return resourceId; }
    QString getResourceName() const { return resourceName; }
    QDate getDate() const { return date; }
    QTime getStartTime() const { return startTime; }
    QTime getEndTime() const { return endTime; }
    QString getStatus() const { return status; }
    double getFee() const { return fee; }
    
    // Setter方法
    void setId(const QString& id) { this->id = id; }
    void setMemberId(const QString& id) { this->memberId = id; }
    void setMemberName(const QString& name) { this->memberName = name; }
    void setType(ReservationType type) { this->type = type; }
    void setResourceId(const QString& id) { this->resourceId = id; }
    void setResourceName(const QString& name) { this->resourceName = name; }
    void setDate(const QDate& date) { this->date = date; }
    void setStartTime(const QTime& time) { this->startTime = time; }
    void setEndTime(const QTime& time) { this->endTime = time; }
    void setStatus(const QString& status) { this->status = status; }
    void setFee(double fee) { this->fee = fee; }
    
    QString getTypeString() const;
    
private:
    QString id;             // 预约ID
    QString memberId;       // 会员ID
    QString memberName;     // 会员姓名
    ReservationType type;   // 预约类型
    QString resourceId;     // 资源ID（课程ID或器械ID）
    QString resourceName;   // 资源名称
    QDate date;             // 预约日期
    QTime startTime;        // 开始时间
    QTime endTime;          // 结束时间
    QString status;         // 状态（已预约/已完成/已取消）
    double fee;             // 费用
};

#endif // RESERVATION_H




