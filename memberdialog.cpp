#include "memberdialog.h"
#include <QMessageBox>

MemberDialog::MemberDialog(QWidget *parent)
    : QDialog(parent), editMode(false)
{
    setupUI();
    setWindowTitle("添加会员");
}

MemberDialog::MemberDialog(const Member& member, QWidget *parent)
    : QDialog(parent), editMode(true)
{
    setupUI();
    loadMemberData(member);
    idEdit->setReadOnly(true);
    setWindowTitle("编辑会员");
}

void MemberDialog::setupUI()
{
    idEdit = new QLineEdit(this);
    nameEdit = new QLineEdit(this);
    phoneEdit = new QLineEdit(this);
    genderCombo = new QComboBox(this);
    genderCombo->addItems(QStringList() << "男" << "女");
    
    joinDateEdit = new QDateEdit(this);
    joinDateEdit->setDate(QDate::currentDate());
    joinDateEdit->setCalendarPopup(true);
    joinDateEdit->setDisplayFormat("yyyy-MM-dd");
    
    balanceSpin = new QDoubleSpinBox(this);
    balanceSpin->setMinimum(0.0);
    balanceSpin->setMaximum(999999.99);
    balanceSpin->setDecimals(2);
    
    statusCombo = new QComboBox(this);
    statusCombo->addItems(QStringList() << "正常" << "暂停" << "到期");
    
    noteEdit = new QTextEdit(this);
    noteEdit->setMaximumHeight(80);
    
    okButton = new QPushButton("确定", this);
    cancelButton = new QPushButton("取消", this);
    
    QFormLayout *formLayout = new QFormLayout();
    formLayout->addRow("会员ID:", idEdit);
    formLayout->addRow("姓名:", nameEdit);
    formLayout->addRow("电话:", phoneEdit);
    formLayout->addRow("性别:", genderCombo);
    formLayout->addRow("入会日期:", joinDateEdit);
    formLayout->addRow("余额:", balanceSpin);
    formLayout->addRow("状态:", statusCombo);
    formLayout->addRow("备注:", noteEdit);
    
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);
    
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(buttonLayout);
    
    connect(okButton, &QPushButton::clicked, this, &MemberDialog::onOkClicked);
    connect(cancelButton, &QPushButton::clicked, this, &MemberDialog::onCancelClicked);
}

void MemberDialog::loadMemberData(const Member& member)
{
    idEdit->setText(member.getId());
    nameEdit->setText(member.getName());
    phoneEdit->setText(member.getPhone());
    genderCombo->setCurrentText(member.getGender());
    joinDateEdit->setDate(member.getJoinDate());
    balanceSpin->setValue(member.getBalance());
    statusCombo->setCurrentText(member.getStatus());
    noteEdit->setPlainText(member.getNote());
}

Member MemberDialog::getMember() const
{
    Member member(idEdit->text().trimmed(), nameEdit->text().trimmed(),
                  phoneEdit->text().trimmed(), genderCombo->currentText(),
                  joinDateEdit->date(), balanceSpin->value());
    member.setStatus(statusCombo->currentText());
    member.setNote(noteEdit->toPlainText());
    return member;
}

void MemberDialog::onOkClicked()
{
    if (idEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "警告", "会员ID不能为空！");
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

void MemberDialog::onCancelClicked()
{
    reject();
}





