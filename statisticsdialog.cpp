#include "statisticsdialog.h"
#include <QHeaderView>
#include <QTableWidgetItem>

StatisticsDialog::StatisticsDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUI();
    updateStatistics();
    setWindowTitle("统计报表");
    resize(600, 500);
}

StatisticsDialog::~StatisticsDialog()
{
}

void StatisticsDialog::setupUI()
{
    memberCountLabel = new QLabel(this);
    coachCountLabel = new QLabel(this);
    courseCountLabel = new QLabel(this);
    activeMemberLabel = new QLabel(this);
    totalRevenueLabel = new QLabel(this);
    
    revenueTable = new QTableWidget(this);
    revenueTable->setColumnCount(3);
    revenueTable->setHorizontalHeaderLabels(QStringList() << "预约ID" << "会员" << "费用");
    revenueTable->horizontalHeader()->setStretchLastSection(true);
    revenueTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    revenueTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    
    refreshButton = new QPushButton("刷新", this);
    closeButton = new QPushButton("关闭", this);
    
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    
    QHBoxLayout *infoLayout1 = new QHBoxLayout();
    infoLayout1->addWidget(memberCountLabel);
    infoLayout1->addWidget(coachCountLabel);
    infoLayout1->addWidget(courseCountLabel);
    
    QHBoxLayout *infoLayout2 = new QHBoxLayout();
    infoLayout2->addWidget(activeMemberLabel);
    infoLayout2->addWidget(totalRevenueLabel);
    infoLayout2->addStretch();
    
    mainLayout->addLayout(infoLayout1);
    mainLayout->addLayout(infoLayout2);
    mainLayout->addWidget(revenueTable);
    
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(refreshButton);
    buttonLayout->addWidget(closeButton);
    mainLayout->addLayout(buttonLayout);
    
    connect(refreshButton, &QPushButton::clicked, this, &StatisticsDialog::refreshStatistics);
    connect(closeButton, &QPushButton::clicked, this, &QDialog::accept);
}

void StatisticsDialog::updateStatistics()
{
    DataManager& dm = DataManager::getInstance();
    
    memberCountLabel->setText(QString("会员总数: %1").arg(dm.getMemberCount()));
    coachCountLabel->setText(QString("教练总数: %1").arg(dm.getCoachCount()));
    courseCountLabel->setText(QString("课程总数: %1").arg(dm.getCourseCount()));
    activeMemberLabel->setText(QString("活跃会员: %1").arg(dm.getActiveMembersCount()));
    totalRevenueLabel->setText(QString("总收入: ¥%1").arg(dm.getTotalRevenue(), 0, 'f', 2));
    
    // 更新收入表格
    revenueTable->setRowCount(0);
    QList<Reservation> reservations = dm.getAllReservations();
    for (const Reservation& r : reservations) {
        if (r.getStatus() == "已完成") {
            int row = revenueTable->rowCount();
            revenueTable->insertRow(row);
            revenueTable->setItem(row, 0, new QTableWidgetItem(r.getId()));
            revenueTable->setItem(row, 1, new QTableWidgetItem(r.getMemberName()));
            revenueTable->setItem(row, 2, new QTableWidgetItem(QString::number(r.getFee(), 'f', 2)));
        }
    }
}

void StatisticsDialog::refreshStatistics()
{
    updateStatistics();
}

