#include "equipdialog.h"
#include <QMessageBox>

EquipDialog::EquipDialog(QWidget *parent)
    : QDialog(parent), editMode(false)
{
    setupUI();
    setWindowTitle("添加器械");
}

EquipDialog::EquipDialog(const Equipment& equipment, QWidget *parent)
    : QDialog(parent), editMode(true)
{
    setupUI();
    loadEquipmentData(equipment);
    idEdit->setReadOnly(true);
    setWindowTitle("编辑器械");
}

void EquipDialog::setupUI()
{
    idEdit = new QLineEdit(this);
    nameEdit = new QLineEdit(this);
    typeEdit = new QLineEdit(this);
    
    purchaseDateEdit = new QDateEdit(this);
    purchaseDateEdit->setDate(QDate::currentDate());
    purchaseDateEdit->setCalendarPopup(true);
    purchaseDateEdit->setDisplayFormat("yyyy-MM-dd");
    
    priceSpin = new QDoubleSpinBox(this);
    priceSpin->setMinimum(0.0);
    priceSpin->setMaximum(999999.99);
    priceSpin->setDecimals(2);
    
    statusCombo = new QComboBox(this);
    statusCombo->addItems(QStringList() << "可用" << "维修中" << "报废");
    
    locationEdit = new QLineEdit(this);
    locationEdit->setPlaceholderText("例如：A区、B区");
    
    maintenanceCountSpin = new QSpinBox(this);
    maintenanceCountSpin->setMinimum(0);
    maintenanceCountSpin->setMaximum(9999);
    
    okButton = new QPushButton("确定", this);
    cancelButton = new QPushButton("取消", this);
    
    QFormLayout *formLayout = new QFormLayout();
    formLayout->addRow("器械ID:", idEdit);
    formLayout->addRow("器械名称:", nameEdit);
    formLayout->addRow("器械类型:", typeEdit);
    formLayout->addRow("购买日期:", purchaseDateEdit);
    formLayout->addRow("价格:", priceSpin);
    formLayout->addRow("状态:", statusCombo);
    formLayout->addRow("位置:", locationEdit);
    formLayout->addRow("维护次数:", maintenanceCountSpin);
    
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);
    
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(buttonLayout);
    
    connect(okButton, &QPushButton::clicked, this, &EquipDialog::onOkClicked);
    connect(cancelButton, &QPushButton::clicked, this, &EquipDialog::onCancelClicked);
}

void EquipDialog::loadEquipmentData(const Equipment& equipment)
{
    idEdit->setText(equipment.getId());
    nameEdit->setText(equipment.getName());
    typeEdit->setText(equipment.getType());
    purchaseDateEdit->setDate(equipment.getPurchaseDate());
    priceSpin->setValue(equipment.getPrice());
    statusCombo->setCurrentText(equipment.getStatus());
    locationEdit->setText(equipment.getLocation());
    maintenanceCountSpin->setValue(equipment.getMaintenanceCount());
}

Equipment EquipDialog::getEquipment() const
{
    Equipment equipment(idEdit->text().trimmed(), nameEdit->text().trimmed(),
                       typeEdit->text().trimmed(), purchaseDateEdit->date(),
                       priceSpin->value());
    equipment.setStatus(statusCombo->currentText());
    equipment.setLocation(locationEdit->text().trimmed());
    equipment.setMaintenanceCount(maintenanceCountSpin->value());
    return equipment;
}

void EquipDialog::onOkClicked()
{
    if (idEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "警告", "器械ID不能为空！");
        idEdit->setFocus();
        return;
    }
    if (nameEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "警告", "器械名称不能为空！");
        nameEdit->setFocus();
        return;
    }
    accept();
}

void EquipDialog::onCancelClicked()
{
    reject();
}





