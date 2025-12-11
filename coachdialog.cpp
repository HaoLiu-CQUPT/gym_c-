#include "coachdialog.h"
#include <QMessageBox>

CoachDialog::CoachDialog(QWidget *parent)
    : QDialog(parent), editMode(false)
{
    setupUI();
    setWindowTitle("添加教练");
}

CoachDialog::CoachDialog(const Coach& coach, QWidget *parent)
    : QDialog(parent), editMode(true)
{
    setupUI();
    loadCoachData(coach);
    idEdit->setReadOnly(true);
    setWindowTitle("编辑教练");
}

void CoachDialog::setupUI()
{
    idEdit = new QLineEdit(this);
    nameEdit = new QLineEdit(this);
    phoneEdit = new QLineEdit(this);
    genderCombo = new QComboBox(this);
    genderCombo->addItems(QStringList() << "男" << "女");
    
    hireDateEdit = new QDateEdit(this);
    hireDateEdit->setDate(QDate::currentDate());
    hireDateEdit->setCalendarPopup(true);
    hireDateEdit->setDisplayFormat("yyyy-MM-dd");
    
    salarySpin = new QDoubleSpinBox(this);
    salarySpin->setMinimum(0.0);
    salarySpin->setMaximum(999999.99);
    salarySpin->setDecimals(2);
    
    specialtyEdit = new QLineEdit(this);
    specialtyEdit->setPlaceholderText("例如：瑜伽、力量训练、有氧运动");
    
    statusCombo = new QComboBox(this);
    statusCombo->addItems(QStringList() << "在职" << "离职");
    
    okButton = new QPushButton("确定", this);
    cancelButton = new QPushButton("取消", this);
    
    QFormLayout *formLayout = new QFormLayout();
    formLayout->addRow("教练ID:", idEdit);
    formLayout->addRow("姓名:", nameEdit);
    formLayout->addRow("电话:", phoneEdit);
    formLayout->addRow("性别:", genderCombo);
    formLayout->addRow("入职日期:", hireDateEdit);
    formLayout->addRow("薪资:", salarySpin);
    formLayout->addRow("专长:", specialtyEdit);
    formLayout->addRow("状态:", statusCombo);
    
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);
    
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(buttonLayout);
    
    connect(okButton, &QPushButton::clicked, this, &CoachDialog::onOkClicked);
    connect(cancelButton, &QPushButton::clicked, this, &CoachDialog::onCancelClicked);
}

void CoachDialog::loadCoachData(const Coach& coach)
{
    idEdit->setText(coach.getId());
    nameEdit->setText(coach.getName());
    phoneEdit->setText(coach.getPhone());
    genderCombo->setCurrentText(coach.getGender());
    hireDateEdit->setDate(coach.getHireDate());
    salarySpin->setValue(coach.getSalary());
    specialtyEdit->setText(coach.getSpecialty());
    statusCombo->setCurrentText(coach.getStatus());
}

Coach CoachDialog::getCoach() const
{
    Coach coach(idEdit->text().trimmed(), nameEdit->text().trimmed(),
                phoneEdit->text().trimmed(), genderCombo->currentText(),
                hireDateEdit->date(), salarySpin->value());
    coach.setSpecialty(specialtyEdit->text().trimmed());
    coach.setStatus(statusCombo->currentText());
    return coach;
}

void CoachDialog::onOkClicked()
{
    if (idEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "警告", "教练ID不能为空！");
        idEdit->setFocus();
        return;
    }
    if (nameEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "警告", "姓名不能为空！");
        nameEdit->setFocus();
        return;
    }
    accept();
}

void CoachDialog::onCancelClicked()
{
    reject();
}




