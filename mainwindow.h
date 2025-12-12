#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QStatusBar>
#include <QLabel>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTableWidget>
#include <QMessageBox>
#include "user.h"
#include "datamanager.h"
#include "memberdialog.h"
#include "coachdialog.h"
#include "coursedialog.h"
#include "equipdialog.h"
#include "reservationdialog.h"
#include "statisticsdialog.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(UserRole role, QWidget *parent = nullptr);
    ~MainWindow();
    
private slots:
    // 会员管理
    void onAddMember();
    void onEditMember();
    void onDeleteMember();
    void onSearchMember();
    void refreshMemberTable();
    
    // 教练管理
    void onAddCoach();
    void onEditCoach();
    void onDeleteCoach();
    void onSearchCoach();
    void refreshCoachTable();
    
    // 课程管理
    void onAddCourse();
    void onEditCourse();
    void onDeleteCourse();
    void refreshCourseTable();
    
    // 器械管理
    void onAddEquipment();
    void onEditEquipment();
    void onDeleteEquipment();
    void onSearchEquipment();
    void refreshEquipmentTable();
    
    // 预约管理
    void onAddReservation();
    void onEditReservation();
    void onDeleteReservation();
    void refreshReservationTable();
    
    // 统计报表
    void onShowStatistics();
    
    // 文件操作
    void onSaveData();
    void onLoadData();
    void onExit();
    
    // 页面切换
    void switchToMemberPage();
    void switchToCoachPage();
    void switchToCoursePage();
    void switchToEquipmentPage();
    void switchToReservationPage();
    void switchToStatisticsPage();

private:
    void setupUI();
    void setupMenuBar();
    void setupStatusBar();
    void setupPages();
    void setupMemberPage();
    void setupCoachPage();
    void setupCoursePage();
    void setupEquipmentPage();
    void setupReservationPage();
    
    UserRole currentRole;
    QStackedWidget *stackedWidget;
    
    // 会员管理页面
    QWidget *memberPage;
    QTableWidget *memberTable;
    QPushButton *addMemberBtn;
    QPushButton *editMemberBtn;
    QPushButton *deleteMemberBtn;
    QPushButton *searchMemberBtn;
    QPushButton *refreshMemberBtn;
    
    // 教练管理页面
    QWidget *coachPage;
    QTableWidget *coachTable;
    QPushButton *addCoachBtn;
    QPushButton *editCoachBtn;
    QPushButton *deleteCoachBtn;
    QPushButton *searchCoachBtn;
    QPushButton *refreshCoachBtn;
    
    // 课程管理页面
    QWidget *coursePage;
    QTableWidget *courseTable;
    QPushButton *addCourseBtn;
    QPushButton *editCourseBtn;
    QPushButton *deleteCourseBtn;
    QPushButton *refreshCourseBtn;
    
    // 器械管理页面
    QWidget *equipmentPage;
    QTableWidget *equipmentTable;
    QPushButton *addEquipmentBtn;
    QPushButton *editEquipmentBtn;
    QPushButton *deleteEquipmentBtn;
    QPushButton *searchEquipmentBtn;
    QPushButton *refreshEquipmentBtn;
    
    // 预约管理页面
    QWidget *reservationPage;
    QTableWidget *reservationTable;
    QPushButton *addReservationBtn;
    QPushButton *editReservationBtn;
    QPushButton *deleteReservationBtn;
    QPushButton *refreshReservationBtn;
    
    // 菜单和动作
    QMenu *memberMenu;
    QMenu *coachMenu;
    QMenu *courseMenu;
    QMenu *equipmentMenu;
    QMenu *reservationMenu;
    QMenu *statisticsMenu;
    QMenu *fileMenu;
    
    QAction *addMemberAction;
    QAction *editMemberAction;
    QAction *deleteMemberAction;
    QAction *addCoachAction;
    QAction *editCoachAction;
    QAction *deleteCoachAction;
    QAction *addCourseAction;
    QAction *editCourseAction;
    QAction *deleteCourseAction;
    QAction *addEquipmentAction;
    QAction *editEquipmentAction;
    QAction *deleteEquipmentAction;
    QAction *addReservationAction;
    QAction *editReservationAction;
    QAction *deleteReservationAction;
    QAction *statisticsAction;
    QAction *saveDataAction;
    QAction *loadDataAction;
    QAction *exitAction;
};

#endif // MAINWINDOW_H





