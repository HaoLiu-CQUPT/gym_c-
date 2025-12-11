#include "datamanager.h"
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QStringConverter>

DataManager::DataManager()
{
    dataDir = "data";
    usersFile = dataDir + "/users.txt";
    membersFile = dataDir + "/members.txt";
    coachesFile = dataDir + "/coaches.txt";
    coursesFile = dataDir + "/courses.txt";
    equipmentFile = dataDir + "/equipment.txt";
    reservationsFile = dataDir + "/reservations.txt";
    
    // 创建数据目录
    QDir dir;
    if (!dir.exists(dataDir)) {
        dir.mkpath(dataDir);
    }
}

DataManager::~DataManager()
{
    saveAllData();
}

DataManager& DataManager::getInstance()
{
    static DataManager instance;
    return instance;
}

// 用户管理
bool DataManager::addUser(const User& user)
{
    if (findUser(user.getUsername())) {
        return false;  // 用户已存在
    }
    users.append(user);
    saveUsers();
    return true;
}

User* DataManager::findUser(const QString& username)
{
    for (int i = 0; i < users.size(); ++i) {
        if (users[i].getUsername() == username) {
            return &users[i];
        }
    }
    return nullptr;
}

bool DataManager::authenticate(const QString& username, const QString& password)
{
    User* user = findUser(username);
    if (user && user->checkPassword(password)) {
        return true;
    }
    return false;
}

// 会员管理
bool DataManager::addMember(const Member& member)
{
    if (findMember(member.getId())) {
        return false;
    }
    members.append(member);
    saveMembers();
    return true;
}

bool DataManager::updateMember(const QString& id, const Member& member)
{
    for (int i = 0; i < members.size(); ++i) {
        if (members[i].getId() == id) {
            members[i] = member;
            saveMembers();
            return true;
        }
    }
    return false;
}

bool DataManager::deleteMember(const QString& id)
{
    for (int i = 0; i < members.size(); ++i) {
        if (members[i].getId() == id) {
            members.removeAt(i);
            saveMembers();
            return true;
        }
    }
    return false;
}

Member* DataManager::findMember(const QString& id)
{
    for (int i = 0; i < members.size(); ++i) {
        if (members[i].getId() == id) {
            return &members[i];
        }
    }
    return nullptr;
}

QList<Member> DataManager::searchMembers(const QString& keyword)
{
    QList<Member> result;
    for (const Member& m : members) {
        if (m.getId().contains(keyword, Qt::CaseInsensitive) ||
            m.getName().contains(keyword, Qt::CaseInsensitive) ||
            m.getPhone().contains(keyword, Qt::CaseInsensitive)) {
            result.append(m);
        }
    }
    return result;
}

// 教练管理
bool DataManager::addCoach(const Coach& coach)
{
    if (findCoach(coach.getId())) {
        return false;
    }
    coaches.append(coach);
    saveCoaches();
    return true;
}

bool DataManager::updateCoach(const QString& id, const Coach& coach)
{
    for (int i = 0; i < coaches.size(); ++i) {
        if (coaches[i].getId() == id) {
            coaches[i] = coach;
            saveCoaches();
            return true;
        }
    }
    return false;
}

bool DataManager::deleteCoach(const QString& id)
{
    for (int i = 0; i < coaches.size(); ++i) {
        if (coaches[i].getId() == id) {
            coaches.removeAt(i);
            saveCoaches();
            return true;
        }
    }
    return false;
}

Coach* DataManager::findCoach(const QString& id)
{
    for (int i = 0; i < coaches.size(); ++i) {
        if (coaches[i].getId() == id) {
            return &coaches[i];
        }
    }
    return nullptr;
}

QList<Coach> DataManager::searchCoaches(const QString& keyword)
{
    QList<Coach> result;
    for (const Coach& c : coaches) {
        if (c.getId().contains(keyword, Qt::CaseInsensitive) ||
            c.getName().contains(keyword, Qt::CaseInsensitive) ||
            c.getPhone().contains(keyword, Qt::CaseInsensitive)) {
            result.append(c);
        }
    }
    return result;
}

// 课程管理
bool DataManager::addCourse(const Course& course)
{
    if (findCourse(course.getId())) {
        return false;
    }
    courses.append(course);
    saveCourses();
    return true;
}

bool DataManager::updateCourse(const QString& id, const Course& course)
{
    for (int i = 0; i < courses.size(); ++i) {
        if (courses[i].getId() == id) {
            courses[i] = course;
            saveCourses();
            return true;
        }
    }
    return false;
}

bool DataManager::deleteCourse(const QString& id)
{
    for (int i = 0; i < courses.size(); ++i) {
        if (courses[i].getId() == id) {
            courses.removeAt(i);
            saveCourses();
            return true;
        }
    }
    return false;
}

Course* DataManager::findCourse(const QString& id)
{
    for (int i = 0; i < courses.size(); ++i) {
        if (courses[i].getId() == id) {
            return &courses[i];
        }
    }
    return nullptr;
}

QList<Course> DataManager::getCoursesByCoach(const QString& coachId)
{
    QList<Course> result;
    for (const Course& c : courses) {
        if (c.getCoachId() == coachId) {
            result.append(c);
        }
    }
    return result;
}

// 器械管理
bool DataManager::addEquipment(const Equipment& equipment)
{
    if (findEquipment(equipment.getId())) {
        return false;
    }
    equipmentList.append(equipment);
    saveEquipment();
    return true;
}

bool DataManager::updateEquipment(const QString& id, const Equipment& equipment)
{
    for (int i = 0; i < equipmentList.size(); ++i) {
        if (equipmentList[i].getId() == id) {
            equipmentList[i] = equipment;
            saveEquipment();
            return true;
        }
    }
    return false;
}

bool DataManager::deleteEquipment(const QString& id)
{
    for (int i = 0; i < equipmentList.size(); ++i) {
        if (equipmentList[i].getId() == id) {
            equipmentList.removeAt(i);
            saveEquipment();
            return true;
        }
    }
    return false;
}

Equipment* DataManager::findEquipment(const QString& id)
{
    for (int i = 0; i < equipmentList.size(); ++i) {
        if (equipmentList[i].getId() == id) {
            return &equipmentList[i];
        }
    }
    return nullptr;
}

QList<Equipment> DataManager::searchEquipment(const QString& keyword)
{
    QList<Equipment> result;
    for (const Equipment& e : equipmentList) {
        if (e.getId().contains(keyword, Qt::CaseInsensitive) ||
            e.getName().contains(keyword, Qt::CaseInsensitive) ||
            e.getType().contains(keyword, Qt::CaseInsensitive)) {
            result.append(e);
        }
    }
    return result;
}

// 预约管理
bool DataManager::addReservation(const Reservation& reservation)
{
    if (findReservation(reservation.getId())) {
        return false;
    }
    reservations.append(reservation);
    saveReservations();
    return true;
}

bool DataManager::updateReservation(const QString& id, const Reservation& reservation)
{
    for (int i = 0; i < reservations.size(); ++i) {
        if (reservations[i].getId() == id) {
            reservations[i] = reservation;
            saveReservations();
            return true;
        }
    }
    return false;
}

bool DataManager::deleteReservation(const QString& id)
{
    for (int i = 0; i < reservations.size(); ++i) {
        if (reservations[i].getId() == id) {
            reservations.removeAt(i);
            saveReservations();
            return true;
        }
    }
    return false;
}

Reservation* DataManager::findReservation(const QString& id)
{
    for (int i = 0; i < reservations.size(); ++i) {
        if (reservations[i].getId() == id) {
            return &reservations[i];
        }
    }
    return nullptr;
}

QList<Reservation> DataManager::getReservationsByMember(const QString& memberId)
{
    QList<Reservation> result;
    for (const Reservation& r : reservations) {
        if (r.getMemberId() == memberId) {
            result.append(r);
        }
    }
    return result;
}

QList<Reservation> DataManager::getReservationsByDate(const QDate& date)
{
    QList<Reservation> result;
    for (const Reservation& r : reservations) {
        if (r.getDate() == date) {
            result.append(r);
        }
    }
    return result;
}

// 文件操作 - 简化版本，使用文本格式
void DataManager::loadUsers()
{
    users.clear();
    QFile file(usersFile);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
        in.setEncoding(QStringConverter::Utf8);
#else
        in.setCodec("UTF-8");
#endif
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split("|");
            if (parts.size() >= 3) {
                UserRole role = UserRole::Reception;
                if (parts[2] == "Admin") role = UserRole::Admin;
                else if (parts[2] == "Coach") role = UserRole::Coach;
                users.append(User(parts[0], parts[1], role));
            }
        }
        file.close();
    } else {
        // 初始化默认用户
        initDefaultData();
    }
}

void DataManager::saveUsers()
{
    QFile file(usersFile);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
        out.setEncoding(QStringConverter::Utf8);
#else
        out.setCodec("UTF-8");
#endif
        for (const User& u : users) {
            QString roleStr = "Reception";
            if (u.getRole() == UserRole::Admin) roleStr = "Admin";
            else if (u.getRole() == UserRole::Coach) roleStr = "Coach";
            out << u.getUsername() << "|" << u.getPassword() << "|" << roleStr << "\n";
        }
        file.close();
    }
}

void DataManager::loadMembers()
{
    members.clear();
    QFile file(membersFile);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
        in.setEncoding(QStringConverter::Utf8);
#else
        in.setCodec("UTF-8");
#endif
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split("|");
            if (parts.size() >= 7) {
                Member m(parts[0], parts[1], parts[2], parts[3], 
                        QDate::fromString(parts[4], "yyyy-MM-dd"), 
                        parts[5].toDouble());
                m.setStatus(parts[6]);
                if (parts.size() > 7) m.setNote(parts[7]);
                members.append(m);
            }
        }
        file.close();
    }
}

void DataManager::saveMembers()
{
    QFile file(membersFile);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
        out.setEncoding(QStringConverter::Utf8);
#else
        out.setCodec("UTF-8");
#endif
        for (const Member& m : members) {
            out << m.getId() << "|" << m.getName() << "|" << m.getPhone() << "|"
                << m.getGender() << "|" << m.getJoinDate().toString("yyyy-MM-dd") << "|"
                << QString::number(m.getBalance()) << "|" << m.getStatus() << "|"
                << m.getNote() << "\n";
        }
        file.close();
    }
}

void DataManager::loadCoaches()
{
    coaches.clear();
    QFile file(coachesFile);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
        in.setEncoding(QStringConverter::Utf8);
#else
        in.setCodec("UTF-8");
#endif
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split("|");
            if (parts.size() >= 7) {
                Coach c(parts[0], parts[1], parts[2], parts[3],
                       QDate::fromString(parts[4], "yyyy-MM-dd"),
                       parts[5].toDouble());
                c.setSpecialty(parts[6]);
                if (parts.size() > 7) c.setStatus(parts[7]);
                coaches.append(c);
            }
        }
        file.close();
    }
}

void DataManager::saveCoaches()
{
    QFile file(coachesFile);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
        out.setEncoding(QStringConverter::Utf8);
#else
        out.setCodec("UTF-8");
#endif
        for (const Coach& c : coaches) {
            out << c.getId() << "|" << c.getName() << "|" << c.getPhone() << "|"
                << c.getGender() << "|" << c.getHireDate().toString("yyyy-MM-dd") << "|"
                << QString::number(c.getSalary()) << "|" << c.getSpecialty() << "|"
                << c.getStatus() << "\n";
        }
        file.close();
    }
}

void DataManager::loadCourses()
{
    courses.clear();
    QFile file(coursesFile);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
        in.setEncoding(QStringConverter::Utf8);
#else
        in.setCodec("UTF-8");
#endif
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split("|");
            if (parts.size() >= 10) {
                Course c(parts[0], parts[1], parts[2], parts[3],
                        QTime::fromString(parts[4], "hh:mm"), 
                        QTime::fromString(parts[5], "hh:mm"),
                        parts[6].toInt(), parts[7].toDouble(), parts[8].toInt());
                c.setCurrentStudents(parts[9].toInt());
                if (parts.size() > 10) c.setDayOfWeek(parts[10]);
                if (parts.size() > 11) c.setStatus(parts[11]);
                courses.append(c);
            }
        }
        file.close();
    }
}

void DataManager::saveCourses()
{
    QFile file(coursesFile);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
        out.setEncoding(QStringConverter::Utf8);
#else
        out.setCodec("UTF-8");
#endif
        for (const Course& c : courses) {
            out << c.getId() << "|" << c.getName() << "|" << c.getCoachId() << "|"
                << c.getCoachName() << "|" << c.getStartTime().toString("hh:mm") << "|"
                << c.getEndTime().toString("hh:mm") << "|" << c.getDuration() << "|"
                << QString::number(c.getPrice()) << "|" << c.getMaxStudents() << "|"
                << c.getCurrentStudents() << "|" << c.getDayOfWeek() << "|"
                << c.getStatus() << "\n";
        }
        file.close();
    }
}

void DataManager::loadEquipment()
{
    equipmentList.clear();
    QFile file(equipmentFile);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
        in.setEncoding(QStringConverter::Utf8);
#else
        in.setCodec("UTF-8");
#endif
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split("|");
            if (parts.size() >= 7) {
                Equipment e(parts[0], parts[1], parts[2],
                           QDate::fromString(parts[3], "yyyy-MM-dd"),
                           parts[4].toDouble());
                e.setStatus(parts[5]);
                e.setLocation(parts[6]);
                if (parts.size() > 7) e.setMaintenanceCount(parts[7].toInt());
                equipmentList.append(e);
            }
        }
        file.close();
    }
}

void DataManager::saveEquipment()
{
    QFile file(equipmentFile);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
        out.setEncoding(QStringConverter::Utf8);
#else
        out.setCodec("UTF-8");
#endif
        for (const Equipment& e : equipmentList) {
            out << e.getId() << "|" << e.getName() << "|" << e.getType() << "|"
                << e.getPurchaseDate().toString("yyyy-MM-dd") << "|"
                << QString::number(e.getPrice()) << "|" << e.getStatus() << "|"
                << e.getLocation() << "|" << e.getMaintenanceCount() << "\n";
        }
        file.close();
    }
}

void DataManager::loadReservations()
{
    reservations.clear();
    QFile file(reservationsFile);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
        in.setEncoding(QStringConverter::Utf8);
#else
        in.setCodec("UTF-8");
#endif
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split("|");
            if (parts.size() >= 10) {
                ReservationType type = parts[3] == "Equipment" ? 
                    ReservationType::Equipment : ReservationType::Course;
                Reservation r(parts[0], parts[1], parts[2], type, parts[4], parts[5],
                            QDate::fromString(parts[6], "yyyy-MM-dd"),
                            QTime::fromString(parts[7], "hh:mm"),
                            QTime::fromString(parts[8], "hh:mm"));
                r.setStatus(parts[9]);
                if (parts.size() > 10) r.setFee(parts[10].toDouble());
                reservations.append(r);
            }
        }
        file.close();
    }
}

void DataManager::saveReservations()
{
    QFile file(reservationsFile);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
        out.setEncoding(QStringConverter::Utf8);
#else
        out.setCodec("UTF-8");
#endif
        for (const Reservation& r : reservations) {
            QString typeStr = r.getType() == ReservationType::Equipment ? 
                "Equipment" : "Course";
            out << r.getId() << "|" << r.getMemberId() << "|" << r.getMemberName() << "|"
                << typeStr << "|" << r.getResourceId() << "|" << r.getResourceName() << "|"
                << r.getDate().toString("yyyy-MM-dd") << "|"
                << r.getStartTime().toString("hh:mm") << "|"
                << r.getEndTime().toString("hh:mm") << "|" << r.getStatus() << "|"
                << QString::number(r.getFee()) << "\n";
        }
        file.close();
    }
}

bool DataManager::loadAllData()
{
    loadUsers();
    loadMembers();
    loadCoaches();
    loadCourses();
    loadEquipment();
    loadReservations();
    return true;
}

bool DataManager::saveAllData()
{
    saveUsers();
    saveMembers();
    saveCoaches();
    saveCourses();
    saveEquipment();
    saveReservations();
    return true;
}

void DataManager::initDefaultData()
{
    // 添加默认管理员账户
    users.append(User("admin", "admin123", UserRole::Admin));
    users.append(User("reception", "123456", UserRole::Reception));
    users.append(User("coach1", "123456", UserRole::Coach));
    saveUsers();
}

double DataManager::getTotalRevenue() const
{
    double total = 0.0;
    for (const Reservation& r : reservations) {
        if (r.getStatus() == "已完成") {
            total += r.getFee();
        }
    }
    return total;
}

int DataManager::getActiveMembersCount() const
{
    int count = 0;
    for (const Member& m : members) {
        if (m.getStatus() == "正常") {
            count++;
        }
    }
    return count;
}

