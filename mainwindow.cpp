#include "mainwindow.h"
#include <QHeaderView>
#include <QInputDialog>
#include <QLabel>
#include <QToolBar>
#include <QSplitter>

MainWindow::MainWindow(UserRole role, QWidget *parent)
    : QMainWindow(parent), currentRole(role)
{
    setupUI();
    setupMenuBar();
    setupStatusBar();
    
    // 根据角色设置权限
    if (currentRole == UserRole::Coach) {
        // 教练只能查看课程和自己的信息
        addCoachAction->setEnabled(false);
        editCoachAction->setEnabled(false);
        deleteCoachAction->setEnabled(false);
        addMemberAction->setEnabled(false);
        editMemberAction->setEnabled(false);
        deleteMemberAction->setEnabled(false);
        addEquipmentAction->setEnabled(false);
        editEquipmentAction->setEnabled(false);
        deleteEquipmentAction->setEnabled(false);
        addReservationAction->setEnabled(false);
        editReservationAction->setEnabled(false);
        deleteReservationAction->setEnabled(false);
        statisticsAction->setEnabled(false);
    } else if (currentRole == UserRole::Reception) {
        // 前台可以管理会员和预约，但不能管理教练和器械
        addCoachAction->setEnabled(false);
        editCoachAction->setEnabled(false);
        deleteCoachAction->setEnabled(false);
        addEquipmentAction->setEnabled(false);
        editEquipmentAction->setEnabled(false);
        deleteEquipmentAction->setEnabled(false);
        statisticsAction->setEnabled(false);
    }
    
    // 默认显示会员管理页面
    switchToMemberPage();
    refreshMemberTable();
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupUI()
{
    setWindowTitle("健身房管理系统");
    resize(1000, 700);
    
    stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);
    
    setupPages();
}

void MainWindow::setupMenuBar()
{
    // 文件菜单
    fileMenu = menuBar()->addMenu("文件(&F)");
    saveDataAction = new QAction("保存数据(&S)", this);
    saveDataAction->setShortcut(QKeySequence::Save);
    loadDataAction = new QAction("加载数据(&L)", this);
    loadDataAction->setShortcut(QKeySequence::Open);
    exitAction = new QAction("退出(&X)", this);
    exitAction->setShortcut(QKeySequence::Quit);
    
    fileMenu->addAction(saveDataAction);
    fileMenu->addAction(loadDataAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);
    
    // 会员管理菜单
    memberMenu = menuBar()->addMenu("会员管理(&M)");
    addMemberAction = new QAction("添加会员(&A)", this);
    editMemberAction = new QAction("编辑会员(&E)", this);
    deleteMemberAction = new QAction("删除会员(&D)", this);
    
    memberMenu->addAction(addMemberAction);
    memberMenu->addAction(editMemberAction);
    memberMenu->addAction(deleteMemberAction);
    
    // 教练管理菜单
    coachMenu = menuBar()->addMenu("教练管理(&C)");
    addCoachAction = new QAction("添加教练(&A)", this);
    editCoachAction = new QAction("编辑教练(&E)", this);
    deleteCoachAction = new QAction("删除教练(&D)", this);
    
    coachMenu->addAction(addCoachAction);
    coachMenu->addAction(editCoachAction);
    coachMenu->addAction(deleteCoachAction);
    
    // 课程管理菜单
    courseMenu = menuBar()->addMenu("课程管理(&R)");
    addCourseAction = new QAction("添加课程(&A)", this);
    editCourseAction = new QAction("编辑课程(&E)", this);
    deleteCourseAction = new QAction("删除课程(&D)", this);
    
    courseMenu->addAction(addCourseAction);
    courseMenu->addAction(editCourseAction);
    courseMenu->addAction(deleteCourseAction);
    
    // 器械管理菜单
    equipmentMenu = menuBar()->addMenu("器械管理(&E)");
    addEquipmentAction = new QAction("添加器械(&A)", this);
    editEquipmentAction = new QAction("编辑器械(&E)", this);
    deleteEquipmentAction = new QAction("删除器械(&D)", this);
    
    equipmentMenu->addAction(addEquipmentAction);
    equipmentMenu->addAction(editEquipmentAction);
    equipmentMenu->addAction(deleteEquipmentAction);
    
    // 预约管理菜单
    reservationMenu = menuBar()->addMenu("预约管理(&R)");
    addReservationAction = new QAction("添加预约(&A)", this);
    editReservationAction = new QAction("编辑预约(&E)", this);
    deleteReservationAction = new QAction("删除预约(&D)", this);
    
    reservationMenu->addAction(addReservationAction);
    reservationMenu->addAction(editReservationAction);
    reservationMenu->addAction(deleteReservationAction);
    
    // 统计报表菜单
    statisticsMenu = menuBar()->addMenu("统计报表(&S)");
    statisticsAction = new QAction("查看统计(&V)", this);
    statisticsMenu->addAction(statisticsAction);
    
    // 连接信号和槽
    connect(saveDataAction, &QAction::triggered, this, &MainWindow::onSaveData);
    connect(loadDataAction, &QAction::triggered, this, &MainWindow::onLoadData);
    connect(exitAction, &QAction::triggered, this, &MainWindow::onExit);
    
    connect(addMemberAction, &QAction::triggered, this, &MainWindow::switchToMemberPage);
    connect(addMemberAction, &QAction::triggered, this, &MainWindow::onAddMember);
    connect(editMemberAction, &QAction::triggered, this, &MainWindow::switchToMemberPage);
    connect(editMemberAction, &QAction::triggered, this, &MainWindow::onEditMember);
    connect(deleteMemberAction, &QAction::triggered, this, &MainWindow::switchToMemberPage);
    connect(deleteMemberAction, &QAction::triggered, this, &MainWindow::onDeleteMember);
    
    connect(addCoachAction, &QAction::triggered, this, &MainWindow::switchToCoachPage);
    connect(addCoachAction, &QAction::triggered, this, &MainWindow::onAddCoach);
    connect(editCoachAction, &QAction::triggered, this, &MainWindow::switchToCoachPage);
    connect(editCoachAction, &QAction::triggered, this, &MainWindow::onEditCoach);
    connect(deleteCoachAction, &QAction::triggered, this, &MainWindow::switchToCoachPage);
    connect(deleteCoachAction, &QAction::triggered, this, &MainWindow::onDeleteCoach);
    
    connect(addCourseAction, &QAction::triggered, this, &MainWindow::switchToCoursePage);
    connect(addCourseAction, &QAction::triggered, this, &MainWindow::onAddCourse);
    connect(editCourseAction, &QAction::triggered, this, &MainWindow::switchToCoursePage);
    connect(editCourseAction, &QAction::triggered, this, &MainWindow::onEditCourse);
    connect(deleteCourseAction, &QAction::triggered, this, &MainWindow::switchToCoursePage);
    connect(deleteCourseAction, &QAction::triggered, this, &MainWindow::onDeleteCourse);
    
    connect(addEquipmentAction, &QAction::triggered, this, &MainWindow::switchToEquipmentPage);
    connect(addEquipmentAction, &QAction::triggered, this, &MainWindow::onAddEquipment);
    connect(editEquipmentAction, &QAction::triggered, this, &MainWindow::switchToEquipmentPage);
    connect(editEquipmentAction, &QAction::triggered, this, &MainWindow::onEditEquipment);
    connect(deleteEquipmentAction, &QAction::triggered, this, &MainWindow::switchToEquipmentPage);
    connect(deleteEquipmentAction, &QAction::triggered, this, &MainWindow::onDeleteEquipment);
    
    connect(addReservationAction, &QAction::triggered, this, &MainWindow::switchToReservationPage);
    connect(addReservationAction, &QAction::triggered, this, &MainWindow::onAddReservation);
    connect(editReservationAction, &QAction::triggered, this, &MainWindow::switchToReservationPage);
    connect(editReservationAction, &QAction::triggered, this, &MainWindow::onEditReservation);
    connect(deleteReservationAction, &QAction::triggered, this, &MainWindow::switchToReservationPage);
    connect(deleteReservationAction, &QAction::triggered, this, &MainWindow::onDeleteReservation);
    
    connect(statisticsAction, &QAction::triggered, this, &MainWindow::onShowStatistics);
}

void MainWindow::setupStatusBar()
{
    statusBar()->showMessage("就绪");
}

void MainWindow::setupPages()
{
    setupMemberPage();
    setupCoachPage();
    setupCoursePage();
    setupEquipmentPage();
    setupReservationPage();
}

void MainWindow::setupMemberPage()
{
    memberPage = new QWidget();
    memberTable = new QTableWidget(memberPage);
    memberTable->setColumnCount(8);
    memberTable->setHorizontalHeaderLabels(
        QStringList() << "会员ID" << "姓名" << "电话" << "性别" 
        << "入会日期" << "余额" << "状态" << "备注");
    memberTable->horizontalHeader()->setStretchLastSection(true);
    memberTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    memberTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    
    addMemberBtn = new QPushButton("添加", memberPage);
    editMemberBtn = new QPushButton("编辑", memberPage);
    deleteMemberBtn = new QPushButton("删除", memberPage);
    searchMemberBtn = new QPushButton("搜索", memberPage);
    refreshMemberBtn = new QPushButton("刷新", memberPage);
    
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(addMemberBtn);
    buttonLayout->addWidget(editMemberBtn);
    buttonLayout->addWidget(deleteMemberBtn);
    buttonLayout->addWidget(searchMemberBtn);
    buttonLayout->addWidget(refreshMemberBtn);
    buttonLayout->addStretch();
    
    QVBoxLayout *mainLayout = new QVBoxLayout(memberPage);
    mainLayout->addWidget(memberTable);
    mainLayout->addLayout(buttonLayout);
    
    connect(addMemberBtn, &QPushButton::clicked, this, &MainWindow::onAddMember);
    connect(editMemberBtn, &QPushButton::clicked, this, &MainWindow::onEditMember);
    connect(deleteMemberBtn, &QPushButton::clicked, this, &MainWindow::onDeleteMember);
    connect(searchMemberBtn, &QPushButton::clicked, this, &MainWindow::onSearchMember);
    connect(refreshMemberBtn, &QPushButton::clicked, this, &MainWindow::refreshMemberTable);
    
    stackedWidget->addWidget(memberPage);
}

void MainWindow::setupCoachPage()
{
    coachPage = new QWidget();
    coachTable = new QTableWidget(coachPage);
    coachTable->setColumnCount(8);
    coachTable->setHorizontalHeaderLabels(
        QStringList() << "教练ID" << "姓名" << "电话" << "性别" 
        << "入职日期" << "薪资" << "专长" << "状态");
    coachTable->horizontalHeader()->setStretchLastSection(true);
    coachTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    coachTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    
    addCoachBtn = new QPushButton("添加", coachPage);
    editCoachBtn = new QPushButton("编辑", coachPage);
    deleteCoachBtn = new QPushButton("删除", coachPage);
    searchCoachBtn = new QPushButton("搜索", coachPage);
    refreshCoachBtn = new QPushButton("刷新", coachPage);
    
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(addCoachBtn);
    buttonLayout->addWidget(editCoachBtn);
    buttonLayout->addWidget(deleteCoachBtn);
    buttonLayout->addWidget(searchCoachBtn);
    buttonLayout->addWidget(refreshCoachBtn);
    buttonLayout->addStretch();
    
    QVBoxLayout *mainLayout = new QVBoxLayout(coachPage);
    mainLayout->addWidget(coachTable);
    mainLayout->addLayout(buttonLayout);
    
    connect(addCoachBtn, &QPushButton::clicked, this, &MainWindow::onAddCoach);
    connect(editCoachBtn, &QPushButton::clicked, this, &MainWindow::onEditCoach);
    connect(deleteCoachBtn, &QPushButton::clicked, this, &MainWindow::onDeleteCoach);
    connect(searchCoachBtn, &QPushButton::clicked, this, &MainWindow::onSearchCoach);
    connect(refreshCoachBtn, &QPushButton::clicked, this, &MainWindow::refreshCoachTable);
    
    stackedWidget->addWidget(coachPage);
}

void MainWindow::setupCoursePage()
{
    coursePage = new QWidget();
    courseTable = new QTableWidget(coursePage);
    courseTable->setColumnCount(9);
    courseTable->setHorizontalHeaderLabels(
        QStringList() << "课程ID" << "课程名称" << "教练" << "开始时间" 
        << "结束时间" << "时长(分钟)" << "价格" << "学员数/最大" << "状态");
    courseTable->horizontalHeader()->setStretchLastSection(true);
    courseTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    courseTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    
    addCourseBtn = new QPushButton("添加", coursePage);
    editCourseBtn = new QPushButton("编辑", coursePage);
    deleteCourseBtn = new QPushButton("删除", coursePage);
    refreshCourseBtn = new QPushButton("刷新", coursePage);
    
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(addCourseBtn);
    buttonLayout->addWidget(editCourseBtn);
    buttonLayout->addWidget(deleteCourseBtn);
    buttonLayout->addWidget(refreshCourseBtn);
    buttonLayout->addStretch();
    
    QVBoxLayout *mainLayout = new QVBoxLayout(coursePage);
    mainLayout->addWidget(courseTable);
    mainLayout->addLayout(buttonLayout);
    
    connect(addCourseBtn, &QPushButton::clicked, this, &MainWindow::onAddCourse);
    connect(editCourseBtn, &QPushButton::clicked, this, &MainWindow::onEditCourse);
    connect(deleteCourseBtn, &QPushButton::clicked, this, &MainWindow::onDeleteCourse);
    connect(refreshCourseBtn, &QPushButton::clicked, this, &MainWindow::refreshCourseTable);
    
    stackedWidget->addWidget(coursePage);
}

void MainWindow::setupEquipmentPage()
{
    equipmentPage = new QWidget();
    equipmentTable = new QTableWidget(equipmentPage);
    equipmentTable->setColumnCount(8);
    equipmentTable->setHorizontalHeaderLabels(
        QStringList() << "器械ID" << "器械名称" << "类型" << "购买日期" 
        << "价格" << "状态" << "位置" << "维护次数");
    equipmentTable->horizontalHeader()->setStretchLastSection(true);
    equipmentTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    equipmentTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    
    addEquipmentBtn = new QPushButton("添加", equipmentPage);
    editEquipmentBtn = new QPushButton("编辑", equipmentPage);
    deleteEquipmentBtn = new QPushButton("删除", equipmentPage);
    searchEquipmentBtn = new QPushButton("搜索", equipmentPage);
    refreshEquipmentBtn = new QPushButton("刷新", equipmentPage);
    
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(addEquipmentBtn);
    buttonLayout->addWidget(editEquipmentBtn);
    buttonLayout->addWidget(deleteEquipmentBtn);
    buttonLayout->addWidget(searchEquipmentBtn);
    buttonLayout->addWidget(refreshEquipmentBtn);
    buttonLayout->addStretch();
    
    QVBoxLayout *mainLayout = new QVBoxLayout(equipmentPage);
    mainLayout->addWidget(equipmentTable);
    mainLayout->addLayout(buttonLayout);
    
    connect(addEquipmentBtn, &QPushButton::clicked, this, &MainWindow::onAddEquipment);
    connect(editEquipmentBtn, &QPushButton::clicked, this, &MainWindow::onEditEquipment);
    connect(deleteEquipmentBtn, &QPushButton::clicked, this, &MainWindow::onDeleteEquipment);
    connect(searchEquipmentBtn, &QPushButton::clicked, this, &MainWindow::onSearchEquipment);
    connect(refreshEquipmentBtn, &QPushButton::clicked, this, &MainWindow::refreshEquipmentTable);
    
    stackedWidget->addWidget(equipmentPage);
}

void MainWindow::setupReservationPage()
{
    reservationPage = new QWidget();
    reservationTable = new QTableWidget(reservationPage);
    reservationTable->setColumnCount(9);
    reservationTable->setHorizontalHeaderLabels(
        QStringList() << "预约ID" << "会员" << "类型" << "资源" 
        << "日期" << "开始时间" << "结束时间" << "状态" << "费用");
    reservationTable->horizontalHeader()->setStretchLastSection(true);
    reservationTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    reservationTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    
    addReservationBtn = new QPushButton("添加", reservationPage);
    editReservationBtn = new QPushButton("编辑", reservationPage);
    deleteReservationBtn = new QPushButton("删除", reservationPage);
    refreshReservationBtn = new QPushButton("刷新", reservationPage);
    
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(addReservationBtn);
    buttonLayout->addWidget(editReservationBtn);
    buttonLayout->addWidget(deleteReservationBtn);
    buttonLayout->addWidget(refreshReservationBtn);
    buttonLayout->addStretch();
    
    QVBoxLayout *mainLayout = new QVBoxLayout(reservationPage);
    mainLayout->addWidget(reservationTable);
    mainLayout->addLayout(buttonLayout);
    
    connect(addReservationBtn, &QPushButton::clicked, this, &MainWindow::onAddReservation);
    connect(editReservationBtn, &QPushButton::clicked, this, &MainWindow::onEditReservation);
    connect(deleteReservationBtn, &QPushButton::clicked, this, &MainWindow::onDeleteReservation);
    connect(refreshReservationBtn, &QPushButton::clicked, this, &MainWindow::refreshReservationTable);
    
    stackedWidget->addWidget(reservationPage);
}

// 会员管理槽函数
void MainWindow::onAddMember()
{
    MemberDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        Member member = dialog.getMember();
        DataManager& dm = DataManager::getInstance();
        if (dm.addMember(member)) {
            QMessageBox::information(this, "成功", "会员添加成功！");
            refreshMemberTable();
        } else {
            QMessageBox::warning(this, "失败", "会员ID已存在！");
        }
    }
}

void MainWindow::onEditMember()
{
    int row = memberTable->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "警告", "请先选择要编辑的会员！");
        return;
    }
    
    QString id = memberTable->item(row, 0)->text();
    DataManager& dm = DataManager::getInstance();
    Member* member = dm.findMember(id);
    if (member) {
        MemberDialog dialog(*member, this);
        if (dialog.exec() == QDialog::Accepted) {
            Member updatedMember = dialog.getMember();
            if (dm.updateMember(id, updatedMember)) {
                QMessageBox::information(this, "成功", "会员信息更新成功！");
                refreshMemberTable();
            }
        }
    }
}

void MainWindow::onDeleteMember()
{
    int row = memberTable->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "警告", "请先选择要删除的会员！");
        return;
    }
    
    QString id = memberTable->item(row, 0)->text();
    QString name = memberTable->item(row, 1)->text();
    
    int ret = QMessageBox::question(this, "确认", 
        QString("确定要删除会员 %1(%2) 吗？").arg(name, id),
        QMessageBox::Yes | QMessageBox::No);
    
    if (ret == QMessageBox::Yes) {
        DataManager& dm = DataManager::getInstance();
        if (dm.deleteMember(id)) {
            QMessageBox::information(this, "成功", "会员删除成功！");
            refreshMemberTable();
        }
    }
}

void MainWindow::onSearchMember()
{
    bool ok;
    QString keyword = QInputDialog::getText(this, "搜索会员", 
        "请输入搜索关键词（ID/姓名/电话）:", QLineEdit::Normal, "", &ok);
    if (ok && !keyword.isEmpty()) {
        DataManager& dm = DataManager::getInstance();
        QList<Member> results = dm.searchMembers(keyword);
        
        memberTable->setRowCount(0);
        for (const Member& m : results) {
            int row = memberTable->rowCount();
            memberTable->insertRow(row);
            memberTable->setItem(row, 0, new QTableWidgetItem(m.getId()));
            memberTable->setItem(row, 1, new QTableWidgetItem(m.getName()));
            memberTable->setItem(row, 2, new QTableWidgetItem(m.getPhone()));
            memberTable->setItem(row, 3, new QTableWidgetItem(m.getGender()));
            memberTable->setItem(row, 4, new QTableWidgetItem(m.getJoinDate().toString("yyyy-MM-dd")));
            memberTable->setItem(row, 5, new QTableWidgetItem(QString::number(m.getBalance(), 'f', 2)));
            memberTable->setItem(row, 6, new QTableWidgetItem(m.getStatus()));
            memberTable->setItem(row, 7, new QTableWidgetItem(m.getNote()));
        }
        statusBar()->showMessage(QString("找到 %1 条记录").arg(results.size()));
    }
}

void MainWindow::refreshMemberTable()
{
    DataManager& dm = DataManager::getInstance();
    QList<Member> members = dm.getAllMembers();
    
    memberTable->setRowCount(0);
    for (const Member& m : members) {
        int row = memberTable->rowCount();
        memberTable->insertRow(row);
        memberTable->setItem(row, 0, new QTableWidgetItem(m.getId()));
        memberTable->setItem(row, 1, new QTableWidgetItem(m.getName()));
        memberTable->setItem(row, 2, new QTableWidgetItem(m.getPhone()));
        memberTable->setItem(row, 3, new QTableWidgetItem(m.getGender()));
        memberTable->setItem(row, 4, new QTableWidgetItem(m.getJoinDate().toString("yyyy-MM-dd")));
        memberTable->setItem(row, 5, new QTableWidgetItem(QString::number(m.getBalance(), 'f', 2)));
        memberTable->setItem(row, 6, new QTableWidgetItem(m.getStatus()));
        memberTable->setItem(row, 7, new QTableWidgetItem(m.getNote()));
    }
    statusBar()->showMessage(QString("共 %1 条记录").arg(members.size()));
}

// 教练管理槽函数（类似会员管理）
void MainWindow::onAddCoach()
{
    CoachDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        Coach coach = dialog.getCoach();
        DataManager& dm = DataManager::getInstance();
        if (dm.addCoach(coach)) {
            QMessageBox::information(this, "成功", "教练添加成功！");
            refreshCoachTable();
        } else {
            QMessageBox::warning(this, "失败", "教练ID已存在！");
        }
    }
}

void MainWindow::onEditCoach()
{
    int row = coachTable->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "警告", "请先选择要编辑的教练！");
        return;
    }
    
    QString id = coachTable->item(row, 0)->text();
    DataManager& dm = DataManager::getInstance();
    Coach* coach = dm.findCoach(id);
    if (coach) {
        CoachDialog dialog(*coach, this);
        if (dialog.exec() == QDialog::Accepted) {
            Coach updatedCoach = dialog.getCoach();
            if (dm.updateCoach(id, updatedCoach)) {
                QMessageBox::information(this, "成功", "教练信息更新成功！");
                refreshCoachTable();
                refreshCourseTable(); // 刷新课程表，因为教练信息可能改变
            }
        }
    }
}

void MainWindow::onDeleteCoach()
{
    int row = coachTable->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "警告", "请先选择要删除的教练！");
        return;
    }
    
    QString id = coachTable->item(row, 0)->text();
    QString name = coachTable->item(row, 1)->text();
    
    int ret = QMessageBox::question(this, "确认", 
        QString("确定要删除教练 %1(%2) 吗？").arg(name, id),
        QMessageBox::Yes | QMessageBox::No);
    
    if (ret == QMessageBox::Yes) {
        DataManager& dm = DataManager::getInstance();
        if (dm.deleteCoach(id)) {
            QMessageBox::information(this, "成功", "教练删除成功！");
            refreshCoachTable();
        }
    }
}

void MainWindow::onSearchCoach()
{
    bool ok;
    QString keyword = QInputDialog::getText(this, "搜索教练", 
        "请输入搜索关键词（ID/姓名/电话）:", QLineEdit::Normal, "", &ok);
    if (ok && !keyword.isEmpty()) {
        DataManager& dm = DataManager::getInstance();
        QList<Coach> results = dm.searchCoaches(keyword);
        
        coachTable->setRowCount(0);
        for (const Coach& c : results) {
            int row = coachTable->rowCount();
            coachTable->insertRow(row);
            coachTable->setItem(row, 0, new QTableWidgetItem(c.getId()));
            coachTable->setItem(row, 1, new QTableWidgetItem(c.getName()));
            coachTable->setItem(row, 2, new QTableWidgetItem(c.getPhone()));
            coachTable->setItem(row, 3, new QTableWidgetItem(c.getGender()));
            coachTable->setItem(row, 4, new QTableWidgetItem(c.getHireDate().toString("yyyy-MM-dd")));
            coachTable->setItem(row, 5, new QTableWidgetItem(QString::number(c.getSalary(), 'f', 2)));
            coachTable->setItem(row, 6, new QTableWidgetItem(c.getSpecialty()));
            coachTable->setItem(row, 7, new QTableWidgetItem(c.getStatus()));
        }
        statusBar()->showMessage(QString("找到 %1 条记录").arg(results.size()));
    }
}

void MainWindow::refreshCoachTable()
{
    DataManager& dm = DataManager::getInstance();
    QList<Coach> coaches = dm.getAllCoaches();
    
    coachTable->setRowCount(0);
    for (const Coach& c : coaches) {
        int row = coachTable->rowCount();
        coachTable->insertRow(row);
        coachTable->setItem(row, 0, new QTableWidgetItem(c.getId()));
        coachTable->setItem(row, 1, new QTableWidgetItem(c.getName()));
        coachTable->setItem(row, 2, new QTableWidgetItem(c.getPhone()));
        coachTable->setItem(row, 3, new QTableWidgetItem(c.getGender()));
        coachTable->setItem(row, 4, new QTableWidgetItem(c.getHireDate().toString("yyyy-MM-dd")));
        coachTable->setItem(row, 5, new QTableWidgetItem(QString::number(c.getSalary(), 'f', 2)));
        coachTable->setItem(row, 6, new QTableWidgetItem(c.getSpecialty()));
        coachTable->setItem(row, 7, new QTableWidgetItem(c.getStatus()));
    }
    statusBar()->showMessage(QString("共 %1 条记录").arg(coaches.size()));
}

// 课程管理槽函数
void MainWindow::onAddCourse()
{
    CourseDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        Course course = dialog.getCourse();
        DataManager& dm = DataManager::getInstance();
        if (dm.addCourse(course)) {
            QMessageBox::information(this, "成功", "课程添加成功！");
            refreshCourseTable();
        } else {
            QMessageBox::warning(this, "失败", "课程ID已存在！");
        }
    }
}

void MainWindow::onEditCourse()
{
    int row = courseTable->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "警告", "请先选择要编辑的课程！");
        return;
    }
    
    QString id = courseTable->item(row, 0)->text();
    DataManager& dm = DataManager::getInstance();
    Course* course = dm.findCourse(id);
    if (course) {
        CourseDialog dialog(*course, this);
        if (dialog.exec() == QDialog::Accepted) {
            Course updatedCourse = dialog.getCourse();
            if (dm.updateCourse(id, updatedCourse)) {
                QMessageBox::information(this, "成功", "课程信息更新成功！");
                refreshCourseTable();
            }
        }
    }
}

void MainWindow::onDeleteCourse()
{
    int row = courseTable->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "警告", "请先选择要删除的课程！");
        return;
    }
    
    QString id = courseTable->item(row, 0)->text();
    QString name = courseTable->item(row, 1)->text();
    
    int ret = QMessageBox::question(this, "确认", 
        QString("确定要删除课程 %1(%2) 吗？").arg(name, id),
        QMessageBox::Yes | QMessageBox::No);
    
    if (ret == QMessageBox::Yes) {
        DataManager& dm = DataManager::getInstance();
        if (dm.deleteCourse(id)) {
            QMessageBox::information(this, "成功", "课程删除成功！");
            refreshCourseTable();
        }
    }
}

void MainWindow::refreshCourseTable()
{
    DataManager& dm = DataManager::getInstance();
    QList<Course> courses = dm.getAllCourses();
    
    courseTable->setRowCount(0);
    for (const Course& c : courses) {
        int row = courseTable->rowCount();
        courseTable->insertRow(row);
        courseTable->setItem(row, 0, new QTableWidgetItem(c.getId()));
        courseTable->setItem(row, 1, new QTableWidgetItem(c.getName()));
        courseTable->setItem(row, 2, new QTableWidgetItem(c.getCoachName()));
        courseTable->setItem(row, 3, new QTableWidgetItem(c.getStartTime().toString("hh:mm")));
        courseTable->setItem(row, 4, new QTableWidgetItem(c.getEndTime().toString("hh:mm")));
        courseTable->setItem(row, 5, new QTableWidgetItem(QString::number(c.getDuration())));
        courseTable->setItem(row, 6, new QTableWidgetItem(QString::number(c.getPrice(), 'f', 2)));
        courseTable->setItem(row, 7, new QTableWidgetItem(
            QString("%1/%2").arg(c.getCurrentStudents()).arg(c.getMaxStudents())));
        courseTable->setItem(row, 8, new QTableWidgetItem(c.getStatus()));
    }
    statusBar()->showMessage(QString("共 %1 条记录").arg(courses.size()));
}

// 器械管理槽函数
void MainWindow::onAddEquipment()
{
    EquipDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        Equipment equipment = dialog.getEquipment();
        DataManager& dm = DataManager::getInstance();
        if (dm.addEquipment(equipment)) {
            QMessageBox::information(this, "成功", "器械添加成功！");
            refreshEquipmentTable();
        } else {
            QMessageBox::warning(this, "失败", "器械ID已存在！");
        }
    }
}

void MainWindow::onEditEquipment()
{
    int row = equipmentTable->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "警告", "请先选择要编辑的器械！");
        return;
    }
    
    QString id = equipmentTable->item(row, 0)->text();
    DataManager& dm = DataManager::getInstance();
    Equipment* equipment = dm.findEquipment(id);
    if (equipment) {
        EquipDialog dialog(*equipment, this);
        if (dialog.exec() == QDialog::Accepted) {
            Equipment updatedEquipment = dialog.getEquipment();
            if (dm.updateEquipment(id, updatedEquipment)) {
                QMessageBox::information(this, "成功", "器械信息更新成功！");
                refreshEquipmentTable();
            }
        }
    }
}

void MainWindow::onDeleteEquipment()
{
    int row = equipmentTable->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "警告", "请先选择要删除的器械！");
        return;
    }
    
    QString id = equipmentTable->item(row, 0)->text();
    QString name = equipmentTable->item(row, 1)->text();
    
    int ret = QMessageBox::question(this, "确认", 
        QString("确定要删除器械 %1(%2) 吗？").arg(name, id),
        QMessageBox::Yes | QMessageBox::No);
    
    if (ret == QMessageBox::Yes) {
        DataManager& dm = DataManager::getInstance();
        if (dm.deleteEquipment(id)) {
            QMessageBox::information(this, "成功", "器械删除成功！");
            refreshEquipmentTable();
        }
    }
}

void MainWindow::onSearchEquipment()
{
    bool ok;
    QString keyword = QInputDialog::getText(this, "搜索器械", 
        "请输入搜索关键词（ID/名称/类型）:", QLineEdit::Normal, "", &ok);
    if (ok && !keyword.isEmpty()) {
        DataManager& dm = DataManager::getInstance();
        QList<Equipment> results = dm.searchEquipment(keyword);
        
        equipmentTable->setRowCount(0);
        for (const Equipment& e : results) {
            int row = equipmentTable->rowCount();
            equipmentTable->insertRow(row);
            equipmentTable->setItem(row, 0, new QTableWidgetItem(e.getId()));
            equipmentTable->setItem(row, 1, new QTableWidgetItem(e.getName()));
            equipmentTable->setItem(row, 2, new QTableWidgetItem(e.getType()));
            equipmentTable->setItem(row, 3, new QTableWidgetItem(e.getPurchaseDate().toString("yyyy-MM-dd")));
            equipmentTable->setItem(row, 4, new QTableWidgetItem(QString::number(e.getPrice(), 'f', 2)));
            equipmentTable->setItem(row, 5, new QTableWidgetItem(e.getStatus()));
            equipmentTable->setItem(row, 6, new QTableWidgetItem(e.getLocation()));
            equipmentTable->setItem(row, 7, new QTableWidgetItem(QString::number(e.getMaintenanceCount())));
        }
        statusBar()->showMessage(QString("找到 %1 条记录").arg(results.size()));
    }
}

void MainWindow::refreshEquipmentTable()
{
    DataManager& dm = DataManager::getInstance();
    QList<Equipment> equipmentList = dm.getAllEquipment();
    
    equipmentTable->setRowCount(0);
    for (const Equipment& e : equipmentList) {
        int row = equipmentTable->rowCount();
        equipmentTable->insertRow(row);
        equipmentTable->setItem(row, 0, new QTableWidgetItem(e.getId()));
        equipmentTable->setItem(row, 1, new QTableWidgetItem(e.getName()));
        equipmentTable->setItem(row, 2, new QTableWidgetItem(e.getType()));
        equipmentTable->setItem(row, 3, new QTableWidgetItem(e.getPurchaseDate().toString("yyyy-MM-dd")));
        equipmentTable->setItem(row, 4, new QTableWidgetItem(QString::number(e.getPrice(), 'f', 2)));
        equipmentTable->setItem(row, 5, new QTableWidgetItem(e.getStatus()));
        equipmentTable->setItem(row, 6, new QTableWidgetItem(e.getLocation()));
        equipmentTable->setItem(row, 7, new QTableWidgetItem(QString::number(e.getMaintenanceCount())));
    }
    statusBar()->showMessage(QString("共 %1 条记录").arg(equipmentList.size()));
}

// 预约管理槽函数
void MainWindow::onAddReservation()
{
    ReservationDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        Reservation reservation = dialog.getReservation();
        DataManager& dm = DataManager::getInstance();
        if (dm.addReservation(reservation)) {
            QMessageBox::information(this, "成功", "预约添加成功！");
            refreshReservationTable();
        } else {
            QMessageBox::warning(this, "失败", "预约ID已存在！");
        }
    }
}

void MainWindow::onEditReservation()
{
    int row = reservationTable->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "警告", "请先选择要编辑的预约！");
        return;
    }
    
    QString id = reservationTable->item(row, 0)->text();
    DataManager& dm = DataManager::getInstance();
    Reservation* reservation = dm.findReservation(id);
    if (reservation) {
        ReservationDialog dialog(*reservation, this);
        if (dialog.exec() == QDialog::Accepted) {
            Reservation updatedReservation = dialog.getReservation();
            if (dm.updateReservation(id, updatedReservation)) {
                QMessageBox::information(this, "成功", "预约信息更新成功！");
                refreshReservationTable();
            }
        }
    }
}

void MainWindow::onDeleteReservation()
{
    int row = reservationTable->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "警告", "请先选择要删除的预约！");
        return;
    }
    
    QString id = reservationTable->item(row, 0)->text();
    
    int ret = QMessageBox::question(this, "确认", 
        QString("确定要删除预约 %1 吗？").arg(id),
        QMessageBox::Yes | QMessageBox::No);
    
    if (ret == QMessageBox::Yes) {
        DataManager& dm = DataManager::getInstance();
        if (dm.deleteReservation(id)) {
            QMessageBox::information(this, "成功", "预约删除成功！");
            refreshReservationTable();
        }
    }
}

void MainWindow::refreshReservationTable()
{
    DataManager& dm = DataManager::getInstance();
    QList<Reservation> reservations = dm.getAllReservations();
    
    reservationTable->setRowCount(0);
    for (const Reservation& r : reservations) {
        int row = reservationTable->rowCount();
        reservationTable->insertRow(row);
        reservationTable->setItem(row, 0, new QTableWidgetItem(r.getId()));
        reservationTable->setItem(row, 1, new QTableWidgetItem(r.getMemberName()));
        reservationTable->setItem(row, 2, new QTableWidgetItem(r.getTypeString()));
        reservationTable->setItem(row, 3, new QTableWidgetItem(r.getResourceName()));
        reservationTable->setItem(row, 4, new QTableWidgetItem(r.getDate().toString("yyyy-MM-dd")));
        reservationTable->setItem(row, 5, new QTableWidgetItem(r.getStartTime().toString("hh:mm")));
        reservationTable->setItem(row, 6, new QTableWidgetItem(r.getEndTime().toString("hh:mm")));
        reservationTable->setItem(row, 7, new QTableWidgetItem(r.getStatus()));
        reservationTable->setItem(row, 8, new QTableWidgetItem(QString::number(r.getFee(), 'f', 2)));
    }
    statusBar()->showMessage(QString("共 %1 条记录").arg(reservations.size()));
}

// 统计报表
void MainWindow::onShowStatistics()
{
    StatisticsDialog dialog(this);
    dialog.exec();
}

// 文件操作
void MainWindow::onSaveData()
{
    DataManager& dm = DataManager::getInstance();
    if (dm.saveAllData()) {
        QMessageBox::information(this, "成功", "数据保存成功！");
        statusBar()->showMessage("数据已保存", 3000);
    } else {
        QMessageBox::warning(this, "失败", "数据保存失败！");
    }
}

void MainWindow::onLoadData()
{
    DataManager& dm = DataManager::getInstance();
    if (dm.loadAllData()) {
        QMessageBox::information(this, "成功", "数据加载成功！");
        refreshMemberTable();
        refreshCoachTable();
        refreshCourseTable();
        refreshEquipmentTable();
        refreshReservationTable();
        statusBar()->showMessage("数据已加载", 3000);
    } else {
        QMessageBox::warning(this, "失败", "数据加载失败！");
    }
}

void MainWindow::onExit()
{
    close();
}

// 页面切换
void MainWindow::switchToMemberPage()
{
    stackedWidget->setCurrentWidget(memberPage);
    refreshMemberTable();
}

void MainWindow::switchToCoachPage()
{
    stackedWidget->setCurrentWidget(coachPage);
    refreshCoachTable();
}

void MainWindow::switchToCoursePage()
{
    stackedWidget->setCurrentWidget(coursePage);
    refreshCourseTable();
}

void MainWindow::switchToEquipmentPage()
{
    stackedWidget->setCurrentWidget(equipmentPage);
    refreshEquipmentTable();
}

void MainWindow::switchToReservationPage()
{
    stackedWidget->setCurrentWidget(reservationPage);
    refreshReservationTable();
}

void MainWindow::switchToStatisticsPage()
{
    onShowStatistics();
}





