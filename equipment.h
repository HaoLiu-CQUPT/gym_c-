#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <QString>
#include <QDate>

// 器械类
class Equipment
{
public:
    Equipment();
    Equipment(const QString& id, const QString& name, const QString& type, 
              const QDate& purchaseDate, double price = 0.0);
    
    // Getter方法
    QString getId() const { return id; }
    QString getName() const { return name; }
    QString getType() const { return type; }
    QDate getPurchaseDate() const { return purchaseDate; }
    double getPrice() const { return price; }
    QString getStatus() const { return status; }
    QString getLocation() const { return location; }
    int getMaintenanceCount() const { return maintenanceCount; }
    
    // Setter方法
    void setId(const QString& id) { this->id = id; }
    void setName(const QString& name) { this->name = name; }
    void setType(const QString& type) { this->type = type; }
    void setPurchaseDate(const QDate& date) { this->purchaseDate = date; }
    void setPrice(double price) { this->price = price; }
    void setStatus(const QString& status) { this->status = status; }
    void setLocation(const QString& location) { this->location = location; }
    void setMaintenanceCount(int count) { this->maintenanceCount = count; }
    
    // 维护
    void maintenance() { maintenanceCount++; }
    
private:
    QString id;             // 器械ID
    QString name;           // 器械名称
    QString type;           // 器械类型
    QDate purchaseDate;     // 购买日期
    double price;           // 价格
    QString status;         // 状态（可用/维修中/报废）
    QString location;       // 位置
    int maintenanceCount;   // 维护次数
};

#endif // EQUIPMENT_H




