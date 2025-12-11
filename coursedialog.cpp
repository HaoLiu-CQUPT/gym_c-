#include "coursedialog.h"
#include "datamanager.h"
#include <QMessageBox>

CourseDialog::CourseDialog(QWidget *parent)
    : QDialog(parent), editMode(false)
{
    setupUI();
    updateCoachCombo();
    setWindowTitle("添加课程");
}

CourseDialog::CourseDialog(const Course& course, QWidget *parent)
    : QDialog(parent), editMode(true)
{
    setupUI();
    updateCoachCombo();
    loadCourseData(course);
    idEdit->setReadOnly(true);
    setWindowTitle("编辑课程");
}

void CourseDialog::setupUI()
{
    idEdit = new QLineEdit(this);
    nameEdit = new QLineEdit(this);
    coachCombo = new QComboBox(this);
    
    startTimeEdit = new QTimeEdit(this);
    startTimeEdit->setTime(QTime(9, 0));
    startTimeEdit->setDisplayFormat("hh:mm");
    
    endTimeEdit = new QTimeEdit(this);
    endTimeEdit->setTime(QTime(10, 0));
    endTimeEdit->setDisplayFormat("hh:mm");
    
    durationSpin = new QSpinBox(this);
    durationSpin->setMinimum(15);
    durationSpin->setMaximum(180);
    durationSpin->setSuffix(" 分钟");
    
    priceSpin = new QDoubleSpinBox(this);
    priceSpin->setMinimum(0.0);
    priceSpin->setMaximum(9999.99);
    priceSpin->setDecimals(2);
    
    maxStudentsSpin = new QSpinBox(this);
    maxStudentsSpin->setMinimum(1);
    maxStudentsSpin->setMaximum(100);
    
    dayOfWeekCombo = new QComboBox(this);
    dayOfWeekCombo->addItems(QStringList() << "星期一" << "星期二" << "星期三" 
                              << "星期四" << "星期五" << "星期六" << "星期日");
    
    statusCombo = new QComboBox(this);
    statusCombo->addItems(QStringList() << "进行中" << "已结束" << "已取消");
    
    okButton = new QPushButton("确定", this);
    cancelButton = new QPushButton("取消", this);
    
    QFormLayout *formLayout = new QFormLayout();
    formLayout->addRow("课程ID:", idEdit);
    formLayout->addRow("课程名称:", nameEdit);
    formLayout->addRow("教练:", coachCombo);
    formLayout->addRow("开始时间:", startTimeEdit);
    formLayout->addRow("结束时间:", endTimeEdit);
    formLayout->addRow("时长:", durationSpin);
    formLayout->addRow("价格:", priceSpin);
    formLayout->addRow("最大学员数:", maxStudentsSpin);
    formLayout->addRow("星期:", dayOfWeekCombo);
    formLayout->addRow("状态:", statusCombo);
    
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);
    
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(buttonLayout);
    
    connect(okButton, &QPushButton::clicked, this, &CourseDialog::onOkClicked);
    connect(cancelButton, &QPushButton::clicked, this, &CourseDialog::onCancelClicked);
}

void CourseDialog::updateCoachCombo()
{
    coachCombo->clear();
    DataManager& dm = DataManager::getInstance();
    QList<Coach> coaches = dm.getAllCoaches();
    for (const Coach& c : coaches) {
        if (c.getStatus() == "在职") {
            coachCombo->addItem(c.getName() + "(" + c.getId() + ")", c.getId());
        }
    }
}

void CourseDialog::loadCourseData(const Course& course)
{
    idEdit->setText(course.getId());
    nameEdit->setText(course.getName());
    
    // 查找教练在combo中的索引
    int index = coachCombo->findData(course.getCoachId());
    if (index >= 0) {
        coachCombo->setCurrentIndex(index);
    }
    
    startTimeEdit->setTime(course.getStartTime());
    endTimeEdit->setTime(course.getEndTime());
    durationSpin->setValue(course.getDuration());
    priceSpin->setValue(course.getPrice());
    maxStudentsSpin->setValue(course.getMaxStudents());
    dayOfWeekCombo->setCurrentText(course.getDayOfWeek());
    statusCombo->setCurrentText(course.getStatus());
}

Course CourseDialog::getCourse() const
{
    QString coachId = coachCombo->currentData().toString();
    QString coachName = coachCombo->currentText().split("(")[0];
    
    Course course(idEdit->text().trimmed(), nameEdit->text().trimmed(),
                  coachId, coachName, startTimeEdit->time(), endTimeEdit->time(),
                  durationSpin->value(), priceSpin->value(), maxStudentsSpin->value());
    course.setDayOfWeek(dayOfWeekCombo->currentText());
    course.setStatus(statusCombo->currentText());
    return course;
}

void CourseDialog::onOkClicked()
{
    if (idEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "警告", "课程ID不能为空！");
        idEdit->setFocus();
        return;
    }
    if (nameEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "警告", "课程名称不能为空！");
        nameEdit->setFocus();
        return;
    }
    if (coachCombo->currentIndex() < 0) {
        QMessageBox::warning(this, "警告", "请选择教练！");
        return;
    }
    accept();
}

void CourseDialog::onCancelClicked()
{
    reject();
}




