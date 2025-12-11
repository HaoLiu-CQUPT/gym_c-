#ifndef COURSE_H
#define COURSE_H

#include <QString>
#include <QTime>
#include <QDate>

// 课程类
class Course
{
public:
    Course();
    Course(const QString& id, const QString& name, const QString& coachId,
           const QString& coachName, const QTime& startTime, const QTime& endTime,
           int duration, double price, int maxStudents);
    
    // Getter方法
    QString getId() const { return id; }
    QString getName() const { return name; }
    QString getCoachId() const { return coachId; }
    QString getCoachName() const { return coachName; }
    QTime getStartTime() const { return startTime; }
    QTime getEndTime() const { return endTime; }
    int getDuration() const { return duration; }
    double getPrice() const { return price; }
    int getMaxStudents() const { return maxStudents; }
    int getCurrentStudents() const { return currentStudents; }
    QString getDayOfWeek() const { return dayOfWeek; }
    QString getStatus() const { return status; }
    
    // Setter方法
    void setId(const QString& id) { this->id = id; }
    void setName(const QString& name) { this->name = name; }
    void setCoachId(const QString& coachId) { this->coachId = coachId; }
    void setCoachName(const QString& coachName) { this->coachName = coachName; }
    void setStartTime(const QTime& time) { this->startTime = time; }
    void setEndTime(const QTime& time) { this->endTime = time; }
    void setDuration(int duration) { this->duration = duration; }
    void setPrice(double price) { this->price = price; }
    void setMaxStudents(int max) { this->maxStudents = max; }
    void setCurrentStudents(int current) { this->currentStudents = current; }
    void setDayOfWeek(const QString& day) { this->dayOfWeek = day; }
    void setStatus(const QString& status) { this->status = status; }
    
    // 增加学员
    bool addStudent();
    
    // 减少学员
    void removeStudent();
    
private:
    QString id;             // 课程ID
    QString name;           // 课程名称
    QString coachId;        // 教练ID
    QString coachName;      // 教练姓名
    QTime startTime;        // 开始时间
    QTime endTime;          // 结束时间
    int duration;           // 时长（分钟）
    double price;           // 价格
    int maxStudents;        // 最大学员数
    int currentStudents;    // 当前学员数
    QString dayOfWeek;      // 星期几
    QString status;         // 状态（进行中/已结束/已取消）
};

#endif // COURSE_H
