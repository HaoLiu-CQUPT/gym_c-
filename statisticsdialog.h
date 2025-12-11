#ifndef STATISTICSDIALOG_H
#define STATISTICSDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTableWidget>
#include "datamanager.h"

class StatisticsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StatisticsDialog(QWidget *parent = nullptr);
    ~StatisticsDialog();

private slots:
    void refreshStatistics();

private:
    void setupUI();
    void updateStatistics();
    
    QLabel *memberCountLabel;
    QLabel *coachCountLabel;
    QLabel *courseCountLabel;
    QLabel *activeMemberLabel;
    QLabel *totalRevenueLabel;
    
    QTableWidget *revenueTable;
    QPushButton *refreshButton;
    QPushButton *closeButton;
};

#endif // STATISTICSDIALOG_H




