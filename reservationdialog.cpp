#include "reservationdialog.h"
#include "datamanager.h"
#include <QMessageBox>

ReservationDialog::ReservationDialog(QWidget *parent)
    : QDialog(parent), editMode(false)
{
    setupUI();
    updateResourceCombo();
    setWindowTitle("添加预约");
}

ReservationDialog::ReservationDialog(const Reservation& reservation, QWidget *parent)
    : QDialog(parent), editMode(true)
{
    setupUI();
    loadReservationData(reservation);
    idEdit->setReadOnly(true);
    setWindowTitle("编辑预约");
}

void ReservationDialog::setupUI()
{
    idEdit = new QLineEdit(this);
    memberCombo = new QComboBox(this);
    typeCombo = new QComboBox(this);
    typeCombo->addItems(QStringList() << "课程预约" << "器械预约");
    
    resourceCombo = new QComboBox(this);
    
    dateEdit = new QDateEdit(this);
    dateEdit->setDate(QDate::currentDate());
    dateEdit->setCalendarPopup(true);
    dateEdit->setDisplayFormat("yyyy-MM-dd");
    dateEdit->setMinimumDate(QDate::currentDate());
    
    startTimeEdit = new QTimeEdit(this);
    startTimeEdit->setTime(QTime(9, 0));
    startTimeEdit->setDisplayFormat("hh:mm");
    
    endTimeEdit = new QTimeEdit(this);
    endTimeEdit->setTime(QTime(10, 0));
    endTimeEdit->setDisplayFormat("hh:mm");
    
    statusCombo = new QComboBox(this);
    statusCombo->addItems(QStringList() << "已预约" << "已完成" << "已取消");
    
    feeSpin = new QDoubleSpinBox(this);
    feeSpin->setMinimum(0.0);
    feeSpin->setMaximum(9999.99);
    feeSpin->setDecimals(2);
    
    okButton = new QPushButton("确定", this);
    cancelButton = new QPushButton("取消", this);
    
    QFormLayout *formLayout = new QFormLayout();
    formLayout->addRow("预约ID:", idEdit);
    formLayout->addRow("会员:", memberCombo);
    formLayout->addRow("预约类型:", typeCombo);
    formLayout->addRow("资源:", resourceCombo);
    formLayout->addRow("日期:", dateEdit);
    formLayout->addRow("开始时间:", startTimeEdit);
    formLayout->addRow("结束时间:", endTimeEdit);
    formLayout->addRow("状态:", statusCombo);
    formLayout->addRow("费用:", feeSpin);
    
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);
    
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(buttonLayout);
    
    connect(okButton, &QPushButton::clicked, this, &ReservationDialog::onOkClicked);
    connect(cancelButton, &QPushButton::clicked, this, &ReservationDialog::onCancelClicked);
    connect(typeCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), 
            this, &ReservationDialog::onTypeChanged);
}

void ReservationDialog::updateResourceCombo()
{
    resourceCombo->clear();
    DataManager& dm = DataManager::getInstance();
    
    // 更新会员下拉框
    memberCombo->clear();
    QList<Member> members = dm.getAllMembers();
    for (const Member& m : members) {
        if (m.getStatus() == "正常") {
            memberCombo->addItem(m.getName() + "(" + m.getId() + ")", m.getId());
        }
    }
    
    // 更新资源下拉框
    if (typeCombo->currentText() == "课程预约") {
        QList<Course> courses = dm.getAllCourses();
        for (const Course& c : courses) {
            if (c.getStatus() == "进行中") {
                resourceCombo->addItem(c.getName() + "(" + c.getId() + ")", c.getId());
            }
        }
    } else {
        QList<Equipment> equipmentList = dm.getAllEquipment();
        for (const Equipment& e : equipmentList) {
            if (e.getStatus() == "可用") {
                resourceCombo->addItem(e.getName() + "(" + e.getId() + ")", e.getId());
            }
        }
    }
}

void ReservationDialog::onTypeChanged(int index)
{
    updateResourceCombo();
}

void ReservationDialog::loadReservationData(const Reservation& reservation)
{
    idEdit->setText(reservation.getId());
    
    // 设置会员
    int memberIndex = memberCombo->findText(reservation.getMemberName());
    if (memberIndex >= 0) {
        memberCombo->setCurrentIndex(memberIndex);
    }
    
    // 设置类型
    int typeIndex = reservation.getType() == ReservationType::Equipment ? 1 : 0;
    typeCombo->setCurrentIndex(typeIndex);
    updateResourceCombo();
    
    // 设置资源
    int resourceIndex = resourceCombo->findData(reservation.getResourceId());
    if (resourceIndex >= 0) {
        resourceCombo->setCurrentIndex(resourceIndex);
    }
    
    dateEdit->setDate(reservation.getDate());
    startTimeEdit->setTime(reservation.getStartTime());
    endTimeEdit->setTime(reservation.getEndTime());
    statusCombo->setCurrentText(reservation.getStatus());
    feeSpin->setValue(reservation.getFee());
}

Reservation ReservationDialog::getReservation() const
{
    QString memberId = memberCombo->currentData().toString();
    QString memberName = memberCombo->currentText().split("(")[0];
    
    ReservationType type = typeCombo->currentIndex() == 1 ? 
        ReservationType::Equipment : ReservationType::Course;
    
    QString resourceId = resourceCombo->currentData().toString();
    QString resourceName = resourceCombo->currentText().split("(")[0];
    
    Reservation reservation(idEdit->text().trimmed(), memberId, memberName,
                           type, resourceId, resourceName,
                           dateEdit->date(), startTimeEdit->time(), endTimeEdit->time());
    reservation.setStatus(statusCombo->currentText());
    reservation.setFee(feeSpin->value());
    return reservation;
}

void ReservationDialog::onOkClicked()
{
    if (idEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "警告", "预约ID不能为空！");
        idEdit->setFocus();
        return;
    }
    if (memberCombo->currentIndex() < 0) {
        QMessageBox::warning(this, "警告", "请选择会员！");
        return;
    }
    if (resourceCombo->currentIndex() < 0) {
        QMessageBox::warning(this, "警告", "请选择资源！");
        return;
    }
    accept();
}

void ReservationDialog::onCancelClicked()
{
    reject();
}

