#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QString>
#include <QList>
#include "member.h"
#include "coach.h"
#include "course.h"
#include "equipment.h"
#include "reservation.h"
#include "user.h"

// 数据管理类 - 使用单例模式
class DataManager
{
public:
    static DataManager& getInstance();
    
    // 用户管理
    bool addUser(const User& user);
    User* findUser(const QString& username);
    bool authenticate(const QString& username, const QString& password);
    
    // 会员管理
    bool addMember(const Member& member);
    bool updateMember(const QString& id, const Member& member);
    bool deleteMember(const QString& id);
    Member* findMember(const QString& id);
    QList<Member> getAllMembers() const { return members; }
    QList<Member> searchMembers(const QString& keyword);
    
    // 教练管理
    bool addCoach(const Coach& coach);
    bool updateCoach(const QString& id, const Coach& coach);
    bool deleteCoach(const QString& id);
    Coach* findCoach(const QString& id);
    QList<Coach> getAllCoaches() const { return coaches; }
    QList<Coach> searchCoaches(const QString& keyword);
    
    // 课程管理
    bool addCourse(const Course& course);
    bool updateCourse(const QString& id, const Course& course);
    bool deleteCourse(const QString& id);
    Course* findCourse(const QString& id);
    QList<Course> getAllCourses() const { return courses; }
    QList<Course> getCoursesByCoach(const QString& coachId);
    
    // 器械管理
    bool addEquipment(const Equipment& equipment);
    bool updateEquipment(const QString& id, const Equipment& equipment);
    bool deleteEquipment(const QString& id);
    Equipment* findEquipment(const QString& id);
    QList<Equipment> getAllEquipment() const { return equipmentList; }
    QList<Equipment> searchEquipment(const QString& keyword);
    
    // 预约管理
    bool addReservation(const Reservation& reservation);
    bool updateReservation(const QString& id, const Reservation& reservation);
    bool deleteReservation(const QString& id);
    Reservation* findReservation(const QString& id);
    QList<Reservation> getAllReservations() const { return reservations; }
    QList<Reservation> getReservationsByMember(const QString& memberId);
    QList<Reservation> getReservationsByDate(const QDate& date);
    
    // 文件操作
    bool loadAllData();
    bool saveAllData();
    void initDefaultData();  // 初始化默认数据
    
    // 统计信息
    int getMemberCount() const { return members.size(); }
    int getCoachCount() const { return coaches.size(); }
    int getCourseCount() const { return courses.size(); }
    double getTotalRevenue() const;
    int getActiveMembersCount() const;
    
private:
    DataManager();
    ~DataManager();
    DataManager(const DataManager&) = delete;
    DataManager& operator=(const DataManager&) = delete;
    
    QList<User> users;
    QList<Member> members;
    QList<Coach> coaches;
    QList<Course> courses;
    QList<Equipment> equipmentList;
    QList<Reservation> reservations;
    
    QString dataDir;
    QString usersFile;
    QString membersFile;
    QString coachesFile;
    QString coursesFile;
    QString equipmentFile;
    QString reservationsFile;
    
    void loadUsers();
    void saveUsers();
    void loadMembers();
    void saveMembers();
    void loadCoaches();
    void saveCoaches();
    void loadCourses();
    void saveCourses();
    void loadEquipment();
    void saveEquipment();
    void loadReservations();
    void saveReservations();
};

#endif // DATAMANAGER_H
