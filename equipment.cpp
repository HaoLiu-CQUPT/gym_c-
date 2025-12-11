#include "equipment.h"

Equipment::Equipment()
    : id(""), name(""), type(""), purchaseDate(QDate::currentDate()), 
      price(0.0), status("可用"), location(""), maintenanceCount(0)
{
}

Equipment::Equipment(const QString& id, const QString& name, const QString& type, 
                     const QDate& purchaseDate, double price)
    : id(id), name(name), type(type), purchaseDate(purchaseDate), 
      price(price), status("可用"), location(""), maintenanceCount(0)
{
}




